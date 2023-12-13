using System.Collections;
using System.Collections.Immutable;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace test2;

public class StudentCollection : IEnumerable<Student>
{
    public List<Student> Students = new List<Student>();

    public void Load(string filepath)
    {
        using FileStream fs = new FileStream(filepath, FileMode.Open, FileAccess.Read);

        StreamReader sr = new StreamReader(fs);

        sr.ReadLine();

        while (!sr.EndOfStream)
        {
            string[] columns = sr.ReadLine().Split(';');

            Student tmp = new Student(columns[0], columns[1], columns[2], int.Parse(columns[3]), int.Parse(columns[4]),
                int.Parse(columns[5]));

            this.Students.Add(tmp);
        }
    }

    public void Sort()
    {
        this.Students.Sort(new StudentComparer());
    }

    public void PrintMathScoreStats()
    {
        Dictionary<int, int> mathScoreStats = new Dictionary<int, int>();

        foreach (Student student in this.Students)
        {
            if (!mathScoreStats.ContainsKey(student.MathScore))
            {
                mathScoreStats[student.MathScore] = 1;
            }
            else
            {
                mathScoreStats[student.MathScore]++;
            }
        }

        foreach (KeyValuePair<int, int> mathScoreStat in mathScoreStats.ToImmutableSortedDictionary())
        {
            if (mathScoreStat.Value > 5)
            {
                Console.WriteLine($"{mathScoreStat.Key}: {mathScoreStat.Value}x");
            }
        }
    }

    public void Save(string filepath)
    {
        using FileStream fs = new FileStream(filepath, FileMode.Create, FileAccess.Write);

        JsonSerializer.Serialize(fs, Students, new JsonSerializerOptions
        {
            WriteIndented = true,
            Encoder = System.Text.Encodings.Web.JavaScriptEncoder.UnsafeRelaxedJsonEscaping
        });
    }

    public IEnumerator<Student> GetEnumerator()
    {
        return this.Students.Where(student => student.MathScore < 60 && student is { Gender: "female", TestStatus: "completed" }).GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }
}

public class StudentComparer : IComparer<Student>
{
    public int Compare(Student? x, Student? y)
    {
        double averageX = (x.MathScore + x.ReadingScore + x.WritingScore) / 3.0;
        double averageY = (y.MathScore + y.ReadingScore + y.WritingScore) / 3.0;

        return -averageX.CompareTo(averageY);
    }
}

public class Student
{
    public string Name { get; set; }
    public string Gender { get; set; }
    [JsonIgnore]
    public string TestStatus { get; set; }
    public int MathScore { get; set; }
    public int ReadingScore { get; set; }
    public int WritingScore { get; set; }

    public Student(string name, string gender, string testStatus, int mathScore, int readingScore, int writingScore)
    {
        this.Name = name;
        this.Gender = gender;
        this.TestStatus = testStatus;
        this.MathScore = mathScore;
        this.ReadingScore = readingScore;
        this.WritingScore = writingScore;
    }
}