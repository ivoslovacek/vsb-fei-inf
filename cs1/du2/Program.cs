using System;
using System.Globalization;

namespace du2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Thread.CurrentThread.CurrentCulture = CultureInfo.GetCultureInfo("cs_CZ");

            if (args.Length == 0)
            {
                Console.WriteLine("Specify a filepath to the CSV!");
                return;
            }

            Schedule schedule = new Schedule();

            try
            {
                string[] lines = File.ReadAllLines(args[0]);

                for (int i = 0; i < lines.Length; i++)
                {
                    switch (lines[i])
                    {
                        case "LECTURE:":
                            {
                                string name = lines[i + 1];
                                string[] time = lines[i + 2].Split(";");
                                DateTime start, end;
                                DateTime.TryParse(time[0], out start);
                                DateTime.TryParse(time[1], out end);

                                Lecture tmp = new Lecture(name, start, end);
                                schedule.Add(tmp);
                                i += 2;
                            }
                            break;

                        case "TUTORIAL:":
                            {
                                string name = lines[i + 1];

                                string[] time = lines[i + 2].Split(";");
                                DateTime start, end;
                                DateTime.TryParse(time[0], out start);
                                DateTime.TryParse(time[1], out end);

                                string[] students = lines[i + 3].Split(";");
                                Student[]? c_students = new Student[students.Length];

                                if (students[0] != "")
                                {
                                    for (int j = 0; j < students.Length; j++)
                                    {
                                        c_students[j] = new Student(students[j]);
                                    }
                                }
                                else
                                {
                                    c_students = null;
                                }

                                Tutorial tmp = new Tutorial(c_students, name, start, end);
                                schedule.Add(tmp);
                                i += 3;
                            }
                            break;

                        case "CONSULTATION:":
                            {
                                string name = lines[i + 1];

                                string[] time = lines[i + 2].Split(";");
                                DateTime start, end;
                                DateTime.TryParse(time[0], out start);
                                DateTime.TryParse(time[1], out end);

                                string location = lines[i + 3];

                                string[] students = lines[i + 4].Split(";");
                                Student[] c_students = new Student[students.Length];

                                if (students[0] != "")
                                {
                                    for (int j = 0; j < students.Length; j++)
                                    {
                                        c_students[j] = new Student(students[j]);
                                    }
                                }

                                Consultation tmp = new Consultation(c_students, location, name, start, end);
                                schedule.Add(tmp);
                                i += 4;
                            }
                            break;

                    }
                }
            }
            catch (FileNotFoundException)
            {
                Console.WriteLine("The file does not exist.");
            }
            catch (IOException e)
            {
                Console.WriteLine("An error occurred while reading the file: " + e.Message);
            };

            System.Console.WriteLine("DNEŠNÍ UDÁLOSTI:");
            System.Console.WriteLine("----------");

            foreach (Event e in schedule[2023, 10, 11])
            {
                System.Console.WriteLine(e.ToString());
            }
            System.Console.WriteLine();

            System.Console.WriteLine("STUDENTI, KTERÉ DNES UVIDÍM:");
            System.Console.WriteLine("----------");

            foreach (Event e in schedule[2023, 10, 11])
            {
                if (e is Tutorial tutorial && tutorial.Students != null)
                {
                    foreach (Student student in tutorial.Students)
                    {
                        if (student != null)
                        {
                            Console.WriteLine($"{student.Name} - {e.Start}");
                        }
                    }
                }
                else if (e is Consultation consultation && consultation.Students != null)
                {
                    foreach (Student student in consultation.Students)
                    {
                        if (student != null)
                        {
                            Console.WriteLine($"{student.Name} - {e.Start}");
                        }
                    }
                }
            }

            System.Console.WriteLine();

            System.Console.WriteLine("ČASY PŘIPOMENUTÍ DNEŠNÍCH UDÁLOSTÍ:");
            System.Console.WriteLine("----------");

            foreach (Event e in schedule[2023, 10, 11])
            {
                System.Console.WriteLine($"{e.ToString()} => {e.GetReminderTime()}");
            }
            System.Console.WriteLine();

            System.Console.WriteLine("BUDOUCÍ UDÁLOSTI:");
            System.Console.WriteLine("----------");

            foreach (Event e in schedule.GetAllUpcoming())
            {
                System.Console.WriteLine(e.ToString());
            }
        }
    }
}
