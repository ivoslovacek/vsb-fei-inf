using MyLib.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyLib.Controllers
{
    class CustomerController
    {

        private static List<Customer> customers = new List<Customer>()
        {
            new Customer(){ Id = 1, Age = 34, IsActive = true, Name = "Jan" },
            new Customer(){ Id = 2, Age = 46, IsActive = false, Name = "Tom" },
            new Customer(){ Id = 3, Age = 36, IsActive = true, Name = "Michala" }
        };

        public string List(int limit)
        {
            StringBuilder result = new StringBuilder();
            int i = 0;
            foreach(var customer in customers)
            {
                if (i < limit)
                {
                    result.AppendLine(customer.Name);
                }
                else
                {
                    break;
                }

                i++;
            }
            return result.ToString();
        }

    }
}
