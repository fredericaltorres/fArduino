 using System;
 using System.Data;
 using System.IO;
 using System.IO.Ports;
 using System.Reflection;
 using ArduinoLibrary;
using DynamicSugar;

namespace TraceWatcher
 {
    public interface ITraceWatcherClient
    {
        
    }

    public class TraceWatcherLed
    {
        private ArduinoConnection _ac;
        private string            _color;
        private int               _blinkRate;
        private int               _blinkStartTime;
        private Boolean           _state;

        public TraceWatcherLed(ArduinoConnection ac, string color)
        {
            _ac = ac;
            _color = color;
        }
        private int GetBlinkDurationCycle() {

            return Environment.TickCount - this._blinkStartTime;
        }
        public void ReverseBlinkMode(int rate)
        {
            if (this.IsBlinking())
                this.SetBlinkModeOff();
            else
                this.SetBlinkMode(rate);
        }
        public void SetBlinkMode(int rate)
        {
            this._blinkRate = rate;
            this._blinkStartTime = Environment.TickCount;
            WriteLine(string.Format("Blink mode {0} rate:{1}", this._color, this._blinkRate), ConsoleColor.Cyan);
        }
        public Boolean IsBlinking() {

            return this._blinkRate != 0;
        }
        public void SetBlinkModeOff() {

            this._blinkRate  = 0;
            this.Set(false);
            WriteLine(string.Format("Blink mode off {0} ", this._color, this._blinkRate), ConsoleColor.Cyan);
        }
        public void Blink() {

            if (GetBlinkDurationCycle() > this._blinkRate)  { // We need to reverse the mode of the led

                this._state = !this._state;
                this.Set(this._state);
                this._blinkStartTime = Environment.TickCount;
            }
        }
        public void Set(Boolean on)
        {
            this._state = on;
            this.SendCommand(this.MakeCommand(this._color, on));
        }
        private string MakeCommand(string color, Boolean on)
        {
            return color + (on ? "On":"Off");
        }
        private void SendCommand(string command)
        {
            WriteLine(command, ConsoleColor.Cyan);
            _ac.Send(command);
        }
        internal static void WriteLine(string text, ConsoleColor c)
        {
            var color = Console.ForegroundColor;
            Console.ForegroundColor = c;
            Console.WriteLine(text);
            Console.ForegroundColor = color;
        }
    }
    
    public class TraceWatcherForArduino : ITraceWatcherClient, IDisposable
    {
        private ArduinoConnection _ac;
        public TraceWatcherLed Red, Green, Yellow;

        public TraceWatcherForArduino(string portName)
        {
            this._ac    = new ArduinoConnection(portName);
            this.Red    = new TraceWatcherLed(_ac, "red");
            this.Yellow = new TraceWatcherLed(_ac, "yellow");
            this.Green  = new TraceWatcherLed(_ac, "green");            
        }

        public void AllOff()
        {
            this.Green.Set(false); 
            this.Red.Set(false);
            this.Yellow.Set(false);
        }
        
        public void BackgroundTask()
        {
            if (_ac.ReceivedMessages.Count > 0)
            {
                var message = _ac.ReceivedMessages.Dequeue();
                TraceWatcherLed.WriteLine(message, message.StartsWith("<") ? ConsoleColor.Green : ConsoleColor.DarkGreen);
            }
            if (this.Red.IsBlinking())
                this.Red.Blink();
            if (this.Yellow.IsBlinking())
            this.Yellow.Blink();
            if (this.Green.IsBlinking())
            this.Green.Blink();
        }

        void IDisposable.Dispose()
        {
            _ac.CloseConnection();
        }
    }

    class Program
    {
        private static void PrintHelp()
        {
            Console.WriteLine("TraceWatcher Win Console");
            Console.WriteLine("R)ed on, Y)ellow, G)reen A)ll off -- C)lear Q)uit");
        }
        static void Main(string[] args)
        {
            var goOn         = true;
            PrintHelp();
            using (var ac = new TraceWatcherForArduino("COM4"))
            {
                Console.WriteLine("Port Open");
                while (goOn)
                {
                    if (Console.KeyAvailable)
                    {
                        var k         = Console.ReadKey(true);
                        var blinkMode = k.Modifiers == ConsoleModifiers.Shift;
                        var offMode   = k.Modifiers != ConsoleModifiers.Control;
                        if (blinkMode)
                        {
                            switch (k.Key)
                            {                            
                                case ConsoleKey.R: ac.Red.ReverseBlinkMode(500);    break;
                                case ConsoleKey.Y: ac.Yellow.ReverseBlinkMode(500); break;
                                case ConsoleKey.G: ac.Green.ReverseBlinkMode(500);  break;
                            }
                        }
                        else
                        {
                            switch (k.Key)
                            {
                                case ConsoleKey.Q: goOn = false; break;
                                case ConsoleKey.C: Console.Clear(); PrintHelp(); break;
                                case ConsoleKey.R: ac.Red.Set(offMode); break;
                                case ConsoleKey.Y: ac.Yellow.Set(offMode); break;
                                case ConsoleKey.G: ac.Green.Set(offMode); break;
                                case ConsoleKey.A: ac.AllOff(); break;
                            }
                        }
                    }
                    ac.BackgroundTask();
                }
            }
        }
    }
 }