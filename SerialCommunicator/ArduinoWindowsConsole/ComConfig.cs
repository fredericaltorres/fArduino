using System;
using System.Collections.Generic;
using System.JSON;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoWindowsConsole
{
    public enum ComCommandType
    {
        Help,
        Quit,
        Send,
        PauseProcessingFromDevice
    }
    public class ComCommand
    {
        public string Caption;
        public string Command;
        public ComCommandType CommandType;
        public ConsoleKey ConsoleKey;
    }
    /// <summary>
    /// Describe the possible communication between the app running on the Arduino and the 
    /// this Windows Console
    /// </summary>
    public class ComConfig : JSonPersistedObject
    {
        public string PortName;
        public string DeviceName;
        public List<ComCommand> ComCommands = new List<ComCommand>();

        public static ComConfig Load(string fileName)
        {
            ComConfig o = JSonPersistedObject.Load<ComConfig>(fileName);
            o.FileName = fileName;
            return o;
        }
        public string GetMenu()
        {
            var b = new StringBuilder();
            foreach (var m in this.ComCommands)
            {
                b.AppendFormat("{0}, ", m.Caption);
            }
            return b.ToString();
        }
        public ComCommand GetCommand(ConsoleKey consoleKey)
        {
            foreach (var m in this.ComCommands)
                if(m.ConsoleKey == consoleKey)
                    return m;
            return null;
        }
    }
}
