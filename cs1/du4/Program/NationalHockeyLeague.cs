using System.Runtime.CompilerServices;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Xml;
using System.Xml.Serialization;

namespace Program;

public class NationalHockeyLeague
{
    public List<Match> Matches { get; set; } = new();
    public List<Team> Teams { get; set; } = new();

    public void LoadData(string teamsCsvPath, string matchCsvPath)
    {
        Dictionary<int, Team> teamDict = new Dictionary<int, Team>();

        OnInvalidDataHandler errorHandler = (string row, int index) => { };

        OnDataCallback teamCallback = (string[] row, int index) =>
        {
            Team tmp = new Team();

            if (index == 0)
            {
                return;
            }

            tmp.Id = int.Parse(row[0]);
            tmp.ShortName = row[1];
            tmp.TeamName = row[2];

            teamDict.Add(tmp.Id, tmp);
        };

        OnDataCallback matchCallback = (string[] row, int index) =>
        {
            Match tmp = new Match();

            if (index == 0)
            {
                return;
            }

            tmp.Season = row[0];
            tmp.Date = DateTime.Parse(row[1]);

            if (!teamDict.ContainsKey(int.Parse(row[2])) || !teamDict.ContainsKey(int.Parse(row[3])))
                return;

            tmp.HomeTeam = teamDict[int.Parse(row[3])];
            tmp.AwayGoals = int.Parse(row[4]);
            tmp.HomeGoals = int.Parse(row[5]);
            tmp.AwayTeam = teamDict[int.Parse(row[2])];

            this.Matches.Add(tmp);
        };

        {
            CsvReader csvReader = new CsvReader(teamsCsvPath);
            csvReader.SetDataCallback(teamCallback);
            csvReader.OnInvalidData += errorHandler;
            csvReader.Read();
        }

        {
            CsvReader csvReader = new CsvReader(matchCsvPath);
            csvReader.SetDataCallback(matchCallback);
            csvReader.OnInvalidData += errorHandler;
            csvReader.Read();
        }

        foreach (KeyValuePair<int, Team> pair in teamDict)
        {
            this.Teams.Add(pair.Value);
        }
    }

    public void ComputeStatistics()
    {
        foreach (Match match in this.Matches)
        {
            if (match.HomeGoals == match.AwayGoals)
            {
                match.HomeTeam.TieCount++;
                match.AwayTeam.TieCount++;
                continue;
            }

            if (match.HomeGoals > match.AwayGoals)
            {
                match.HomeTeam.WinCount++;
                match.AwayTeam.LossCount++;
            }
            else
            {
                match.HomeTeam.LossCount++;
                match.AwayTeam.WinCount++;
            }
        }
    }

    // TODO: implement sorting stuff, most likely trought comparators 
    public void SortTeams()
    {
        this.Teams.Sort(new TeamComparer());
    }

    public IEnumerable<Match> GetMatchesByTeam(Team team)
    {
        return this.Matches.Where(match => match.HomeTeam == team || match.AwayTeam == team);
    }

    public void SaveTeamsToJson(string filePath)
    {
        using FileStream fs = new FileStream(filePath, FileMode.Create, FileAccess.Write);

        JsonSerializer.Serialize(fs, this.Teams, new JsonSerializerOptions
        {
            WriteIndented = true
        });
    }

    public void SaveTeamsToXml(string filePath)
    {
        using FileStream fs = new FileStream(filePath, FileMode.Create, FileAccess.Write);

        using XmlWriter xmlWriter = XmlWriter.Create(fs, new XmlWriterSettings
        {
            Indent = true,
            Encoding = new UTF8Encoding(encoderShouldEmitUTF8Identifier: false)
        });

        XmlSerializer xmlSerializer = new XmlSerializer(typeof(List<Team>));
        xmlSerializer.Serialize(xmlWriter, this.Teams);
    }

    public List<Team> LoadTeamsFromJson(string filePath)
    {
        using FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read);
        List<Team> teams = JsonSerializer.Deserialize<List<Team>>(fs);

        return teams;
    }

    public List<Team> LoadTeamsFromXml(string filePath)
    {
        var serializer = new XmlSerializer(typeof(List<Team>));
        using FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read);
        List<Team> teams = (List<Team>)serializer.Deserialize(fs);

        return teams;
    }
}

public class TeamComparer : IComparer<Team>
{
    public int Compare(Team x, Team y)
    {
        int result = 0;

        int xWinLost = x.WinCount - x.LossCount;
        int yWinLost = y.WinCount - y.LossCount;

        if ((result = xWinLost.CompareTo(yWinLost)) != 0)
        {
            return -result;
        }
        else
        {
            return -x.TieCount.CompareTo(y.TieCount);
        }
    }
}

public class Team
{
    [XmlAttribute("Id")] public int Id { get; set; }
    public string ShortName { get; set; }

    [JsonPropertyName("Name")]
    [XmlElement("Name")]
    public string TeamName { get; set; }

    [JsonIgnore][XmlIgnore] public int LossCount { get; set; } = 0;
    [JsonIgnore][XmlIgnore] public int TieCount { get; set; } = 0;
    [JsonIgnore][XmlIgnore] public int WinCount { get; set; } = 0;
}

public class Match
{
    public int AwayGoals { get; set; }
    public Team AwayTeam { get; set; }
    public DateTime Date { get; set; }
    public int HomeGoals { get; set; }
    public Team HomeTeam { get; set; }
    public string Season { get; set; }
}
