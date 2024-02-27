using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;




namespace ReflectionApp
{
    public class Program
    {
        public static void Main(string[] args)
        {
            string path = Path.GetFullPath("../../../../MyLib/bin/Debug/net6.0/MyLib.dll");
            
            Assembly assembly = Assembly.LoadFile(path);
            
            Console.WriteLine(assembly.FullName);

            Type[] types = assembly.GetTypes();

            object obj = assembly.CreateInstance("MyLib.Controllers.CustomerController");

            Type controllerType = assembly.GetType("MyLib.Controllers.CustomerController");
            MethodInfo listMethod = controllerType.GetMethod("List");

            string result = (string)listMethod.Invoke(obj, new object[] { 2 });
            
            Console.WriteLine(result);

            string url = "/Customer/List?limit=2";

            string[] parts = url.Split('?');
            string[] left = parts[0].Split('/');
            string[] right = parts[1].Split('&');

            string controllerName = left[1];
            string methodName = left[2];

            Dictionary<string, string> arguments = right.Select(x => x.Split('=')).ToDictionary(x => x[0], y => y[1]);












            object customerobj = assembly.CreateInstance("Mylib.Models.Customer");



        }
    }
}