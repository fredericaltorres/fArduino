 using System;
 using System.IO.Ports;
 using ArduinoLibrary;

namespace test
 {
    class Program
    {
        static void WriteLine(string text, ConsoleColor c)
        {
            var color = Console.ForegroundColor;
            Console.ForegroundColor = c;
            Console.WriteLine(text);
            Console.ForegroundColor = color;
        }

        static void SendCommand(ArduinoConnection ac , string command)
        {
            WriteLine(command, ConsoleColor.Cyan);
            ac.Send(command);
        }

        static void PrintHelp(string portName)
        {
            Console.WriteLine("Communication to Arduino, port:{0}", portName);
            Console.WriteLine("Q)uit L)ed R)eset Counter I)nc Counter G)et Counter H)elp");
        }

        static void Main(string[] args)
        {
            var goOn        = true;
            string portName = "COM4";

            PrintHelp(portName);

            using (var ac = new ArduinoConnection(portName))
            {
                Console.WriteLine("Port Open");
                while (goOn)
                {
                    if (Console.KeyAvailable)
                    {
                        switch (Console.ReadKey(true).Key)
                        {
                            case ConsoleKey.H:
                                Console.Clear();
                                PrintHelp(portName);                 
                                break;
                            case ConsoleKey.Q: goOn = false;                        break;

                            case ConsoleKey.R: SendCommand(ac, "resetCounter");     break;
                            case ConsoleKey.I: SendCommand(ac, "incCounter");       break;
                            case ConsoleKey.G: SendCommand(ac, "getCounter");       break;

                            case ConsoleKey.L: SendCommand(ac, "led");              break;
                            case ConsoleKey.S: SendCommand(ac, "invalid");          break;
                        }
                    }
                    if (ac.ReceivedMessages.Count > 0)
                    {
                        var message = ac.ReceivedMessages.Dequeue();
                        if (message.StartsWith("["))
                            WriteLine(message, ConsoleColor.Green);
                        else 
                            WriteLine(message, ConsoleColor.DarkGreen);
                    }
                }
            }
        }
    }
 }