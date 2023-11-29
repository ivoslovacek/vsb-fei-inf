using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.Json;
using Tutorial10.BinaryFormatterExample;
using Tutorial10.DataContractExample;
using Tutorial10.DataContractJsonExample;
using Tutorial10.JsonSerializerExample;
using Tutorial10.XmlSerializerExample;

namespace Tutorial10
{
    internal class Program
    {
        static void Main(string[] args)
        {
            DataContractSerialization.Run();

            DataContractJsonSerialization.Run();

            BinarySerialization.Run();

            XmlSerialization.Run();

            JsonSerialization.Run();

            Console.WriteLine();
        }
    }
}
