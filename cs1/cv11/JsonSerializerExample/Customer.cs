using System;
using System.Collections.Generic;
using System.Text;
using System.Text.Json.Serialization;
using Tutorial10.Commons;

namespace Tutorial10.JsonSerializerExample
{
    public class Customer : ICustomer<Order>
    {
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Name { get; set; }

        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public int Age { get; set; }

        [JsonPropertyName("ContactEmail")]
        public string Email { get; set; }

        [JsonIgnore]
        public double? Weight { get; set; }

        public bool IsAlive { get; set; }
        public Order[] Orders { get; set; }
    }
}
