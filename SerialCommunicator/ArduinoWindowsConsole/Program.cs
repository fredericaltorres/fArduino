using System;
using System.Data;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using ArduinoLibrary;
using ArduinoWindowsConsole;
using DynamicSugar;
using System.Runtime.InteropServices;

namespace test
 {
    class Program
    {
        // http://stackoverflow.com/questions/3549605/add-winlogon-login-method-using-c-sharp-and-yubikey
        [DllImport("user32.dll")]
        public static extern bool LockWorkStation();
        // https://medium.com/@tylermenezes/rfid-credential-provider-d0bf8ef29b16
        // https://github.com/tylermenezes/Rfid-Credential-Provider

        private static ComConfig _comConfig;

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

        private static void PrintHelp()
        {
            WriteLine("Communication to {0} - (port:{1})".FormatString(_comConfig.DeviceName, _comConfig.PortName), ConsoleColor.Cyan);
            WriteLine(_comConfig.GetMenu(), ConsoleColor.Cyan);
        }

        static string GetConfigFileName()
        {
            return Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), "ArduinoWindowsConsole.json");
        }

        static void InitConfig()
        {
            _comConfig = ComConfig.Load(GetConfigFileName());

            //_comConfig = new ComConfig();
            //_comConfig.PortName = "COM4";
            //_comConfig.ComCommands.Add(new ComCommand() { ConsoleKey = System.ConsoleKey.H, Caption = "H)elp",     Command = null,          CommandType = ComCommandType.Help });
            //_comConfig.ComCommands.Add(new ComCommand() { ConsoleKey = System.ConsoleKey.Q, Caption = "Q)uit",     Command = null,          CommandType = ComCommandType.Quit });
            //_comConfig.ComCommands.Add(new ComCommand() { ConsoleKey = System.ConsoleKey.P, Caption = "P)ause",    Command = null,          CommandType = ComCommandType.PauseProcessingFromDevice });
            //_comConfig.ComCommands.Add(new ComCommand() { ConsoleKey = System.ConsoleKey.A, Caption = "A)cquire",  Command = "acquireData", CommandType = ComCommandType.Send });
            //_comConfig.ComCommands.Add(new ComCommand() { ConsoleKey = System.ConsoleKey.R, Caption = "R)eset",    Command = "resetData",   CommandType = ComCommandType.Send });
            //_comConfig.ComCommands.Add(new ComCommand() { ConsoleKey = System.ConsoleKey.G, Caption = "G)et Data", Command = "getData",     CommandType = ComCommandType.Send });
            //_comConfig.ComCommands.Add(new ComCommand() { ConsoleKey = System.ConsoleKey.Add, Caption = "+", Command = "getData",     CommandType = ComCommandType.Send });
            //_comConfig.ComCommands.Add(new ComCommand() { ConsoleKey = System.ConsoleKey.Subtract, Caption = "-", Command = "getData",     CommandType = ComCommandType.Send });

            //_comConfig.ComCommands.Add(new ComCommand() { ConsoleKey = System.ConsoleKey.RightArrow, Caption = "-", Command = "right",     CommandType = ComCommandType.Send });
            //_comConfig.ComCommands.Add(new ComCommand() { ConsoleKey = System.ConsoleKey.LeftArrow, Caption = "-", Command = "left",     CommandType = ComCommandType.Send });

            //_comConfig.Save(@"D:\DVT\Arduino\fArduino\SerialCommunicator\ArduinoWindowsConsole\c.json");
        }

        static void Main(string[] args)
        {
            var goOn         = true;
            var processQueue = true;

            InitConfig();

            PrintHelp();

            using (var ac = new ArduinoConnection(_comConfig.PortName, _comConfig.BaudRate))
            {
                Console.WriteLine("Port Open");
                while (goOn)
                {
                    if (Console.KeyAvailable)
                    {
                        var k = Console.ReadKey(true).Key;
                        var comCommand = _comConfig.GetCommand(k);
                        switch (comCommand.CommandType)
                        {
                            case ComCommandType.Send                     : SendCommand(ac, comCommand.Command);                                               break;
                            case ComCommandType.Help                     : Console.Clear(); PrintHelp();                                   break;
                            case ComCommandType.Quit                     : goOn = false;                                                                      break;
                            case ComCommandType.PauseProcessingFromDevice: processQueue = !processQueue; Console.WriteLine("ProcessQueue:{0}", processQueue); break;
                        }
                    }
                    if (processQueue && ac.ReceivedMessages.Count > 0)
                    {
                        var message = ac.ReceivedMessages.Dequeue();
                        WriteLine(message, message.StartsWith("<") ? ConsoleColor.Green : ConsoleColor.DarkGreen);
                        //if (message.Contains("<MotionDetected>"))
                        //    LockWorkStation();
                    }
                }
            }
        }
    }
 }