using System.Text.RegularExpressions;
using System.Xml;

namespace cv05
{
    internal class Program
    {
        static void Main(string[] args)
        {
            XmlDocument xDoc = new XmlDocument();

            XmlNode root = xDoc.CreateElement("koren");
            xDoc.AppendChild(root);

            XmlNode child1 = xDoc.CreateElement("potomek");
            root.AppendChild(child1);
            
            XmlNode child2 = xDoc.CreateElement("potomek");
            root.AppendChild(child2);

            XmlNode txtNode = xDoc.CreateTextNode("tak to je hodně banger");
            child1.AppendChild(txtNode);
            
            xDoc.Save("test.xml");
        }
        
        public void regex_examples()
        {
            Regex regex = new Regex("^[-zA-Z]{3}[0-9]{3,4}$");
            Console.WriteLine(regex.IsMatch("SLO0168"));


            Regex emailregex = new Regex(@"^([\a-zA-Z-0-9]+[\.\-]*)+@([\a-zA-Z-0-9]+[\.\-]*)+\.[a-z]{2,}$");
            Console.WriteLine(emailregex.IsMatch("ivo.slovacek.st@všb.cz"));
            Console.WriteLine(emailregex.IsMatch("slo0168@vsb.cz"));

            Regex parserRegex = new Regex(@"^(https?):\/\/(([a-z\.]+)\.)?([a-z]+\.cz)");
            string[] urls = new string[]
            {
                "https://katedrainformatiky.cz/cs/pro-uchazece/zamereni-studia",
                "http://katedrainformatiky.cz/",
                "https://katedrainformatiky.cz?page=5",
                "https://page.katedrainformatiky.cz?url=http://test.cz/",
                "https://kelvin.cs.vsb.cz/..."
            };

            foreach (var url in urls)
            {
                Match match = parserRegex.Match(url);
                if (!match.Success)
                {
                    Console.WriteLine($"{url} není url");
                }
                else
                {
                    Console.WriteLine(url);
                    Console.WriteLine(match.Groups[1].Value);
                    Console.WriteLine(match.Groups[2].Value);
                    Console.WriteLine(match.Groups[3].Value);
                    Console.WriteLine(match.Groups[4].Value);
                }

                Console.WriteLine();
            }

            string txt = "Ahoj {name}. Tvá objednávka \"{orderName}\" v ceně {price} byla uspěšně uhrazena";

            Dictionary<string, string> dict = new Dictionary<string, string>()
            {
                { "name", "Ivo" },
                { "orderName", "auta" },
                { "price", "1999.90" }
            };

            Regex placeholderRegex = new Regex(@"\{([a-zA-Z]+)\}");

            string finaltxt = placeholderRegex.Replace(txt, (Match match) =>
            {
                string key = match.Groups[1].Value;
                if (dict.TryGetValue(key, out string value))
                {
                    return value;
                }

                return key.ToUpperInvariant();
            });

            Console.WriteLine(finaltxt);
        }
    }
}

