using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml.Serialization;
using Tutorial10.Commons;

namespace Tutorial10.XmlSerializerExample
{
    internal class XmlSerialization
    {

        public static void Run()
        {
            Customer customer = new Customer()
            {
                Name = "Jan",
                Age = 30,
                Email = "jan@vsb.cz",
                Weight = 75.4,
                IsAlive = true,
                Orders = new Order[] {
                    new Order() {
                        Price = 400,
                        Name = "Dort"
                    },
                    new Order() {
                        Price = 20.5,
                        Name = "Koláč"
                    }
                }
            };

            // using FileStream fs = new FileStream("data-3.xml", FileMode.Create);

            MemoryStream fs = new MemoryStream();

            XmlSerializer serializer = new XmlSerializer(typeof(Customer));
            serializer.Serialize(fs, customer);

            string txt = Encoding.UTF8.GetString(fs.ToArray());
            Console.WriteLine(txt);
            fs.Seek(0, SeekOrigin.Begin);

            Customer c = (Customer)serializer.Deserialize(fs);

            CustomerHelper.Print(c);
        }
    }
}
