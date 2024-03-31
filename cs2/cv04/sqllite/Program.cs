using Dapper;
using Microsoft.Data.Sqlite;

namespace cv04
{
    internal class Program
    {
        void FirstExample()
        {
            string connectionString = "Data Source=mydb.db;";
            using (SqliteConnection connection = new SqliteConnection(connectionString))
            {
                connection.Open();

                using SqliteCommand cmd = connection.CreateCommand();
                // cmd.CommandText = File.ReadAllText("../../../database-create.sql");
                // cmd.ExecuteNonQuery();

                //    cmd.CommandText = "insert into customer (name, address) values (@Name, @Address)";
                cmd.Parameters.AddWithValue("Name", "Ivo");
                // cmd.Parameters.AddWithValue("Address", "Ostrava");

                cmd.Parameters.Add(new SqliteParameter()
                {
                    ParameterName = "Address",
                    Value = "Ostrava",
                    DbType = System.Data.DbType.String
                });

                cmd.ExecuteNonQuery();

                using SqliteCommand selectCountCmd = connection.CreateCommand();
                selectCountCmd.CommandText = "select count(*) from customer";
                long count = (long)selectCountCmd.ExecuteScalar();
                
                Console.WriteLine(count);

                using SqliteCommand selectCmd = connection.CreateCommand();
                selectCmd.CommandText = "select id, name, address from customer";
                using SqliteDataReader reader  = selectCmd.ExecuteReader();

                while (reader.Read())
                {
                    int id = reader.GetInt32(reader.GetOrdinal("id"));
                    string name = reader.GetString(reader.GetOrdinal("name"));
                    string address = reader.GetString(reader.GetOrdinal("address"));
                    Console.WriteLine($"{id}: {name} - {address}");
                }
            }
        }
        
        static void Main(string[] args)
        {
            SimpleCRUD.SetDialect(SimpleCRUD.Dialect.SQLite);
            
            string connectionString = "Data Source=mydb.db;";

            using (SqliteConnection connection = new SqliteConnection(connectionString))
            {
                connection.Open();
                int? id = connection.Insert(new Customer() { Name = "Karlos", Address = "Karlovy Vary" });

                long count = connection.ExecuteScalar<long>("select count(*) from customer");
                Console.WriteLine(count);

                IEnumerable<Customer> customers = connection.Query<Customer>("select * from customer");

                using SqliteTransaction tran = connection.BeginTransaction();
                Customer customer2 = connection.Get<Customer>(id);
                customer2.Address = "Ustí";
                connection.Update(customer2, tran);
                tran.Commit();
                
                foreach (Customer customer in customers)
                {
                    Console.WriteLine($"{customer.Id} : {customer.Name}, {customer.Address}"); 
                }
            }
        }
    };

    public class Customer
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public string Address { get; set; }
    }
};