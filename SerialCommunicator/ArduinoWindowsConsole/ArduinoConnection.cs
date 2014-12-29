using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Threading;

namespace ArduinoLibrary
{

    /// <summary>
    /// provides very low level access to the serial _serialPort that an ardiuno is plugged in to
    /// </summary>
    public class ArduinoConnection : IDisposable 
    {
        SerialPort _serialPort;
        public string PortName  { get; set; }
        public int BaudRate     { get; set; }

        private StringBuilder _textReceived = new StringBuilder(1024);

        public Queue<String> ReceivedMessages = new Queue<string>();

        public ArduinoConnection(string portName)
        {
            this.BaudRate       = 9600;
            _serialPort         = new SerialPort(portName);
            this.PortName       = portName;
            _serialPort.ErrorReceived += new SerialErrorReceivedEventHandler(port_ErrorReceived);
            _serialPort.DataReceived  += new SerialDataReceivedEventHandler(port_DataReceived);

            if (this.Open())
            {
                this._serialPort.DiscardInBuffer();
                this._serialPort.DiscardOutBuffer();
            }
            else
            {
                throw new ApplicationException(string.Format("Cannot open port:{0}", portName));
            }
        }

        private bool Open(int retryCount = 5, int waitTime = 2000)
        {
            int count = 0;
            while (count < retryCount)
            {
                try
                {
                    this._serialPort.Open();
                    return true;
                }
                catch (System.Exception ex)
                {
                    Thread.Sleep(waitTime);
                }
            }
            return false;
        }

        public void Send(string text)
        {
            this._serialPort.WriteLine(text);
        }

        public bool IsConnected
        {
            get { return _serialPort.IsOpen; }
        }

        void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            var s = this._serialPort.ReadExisting();
            _textReceived.Append(s);
            if (_textReceived.ToString().EndsWith("\n"))
            {
                var text = _textReceived.ToString().Replace("\n", "");
                ReceivedMessages.Enqueue(text);
                _textReceived.Clear();
            }
        }

        void port_ErrorReceived(object sender, SerialErrorReceivedEventArgs e)
        {
            Console.WriteLine("Error:{0}", e.EventType);
        }

        public static string[] GetAvailablePorts()
        {
            return SerialPort.GetPortNames();
        }

        public void CloseConnection()
        {
            if (_serialPort.IsOpen)
                _serialPort.Close();
        }

        public virtual void Dispose()
        {
            CloseConnection();
        }
    }
}