using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ValidatorSatellite
{
    public class Serial
    {
        private SerialPort SerialCom;
        private Message RecvMessage;
        public List<Action<Message>> RecvMessageActions;
        private bool RecvLoop;
        private byte[] buffer;


        public Serial()
        {
            this.SerialCom = new SerialPort();
            this.RecvMessage = new Message();
            this.RecvMessageActions = new List<Action<Message>>();
            this.RecvLoop = false;
            this.buffer = new byte[512];

        }

        public void Init(int baudrate, int dataBits, StopBits stopBits, Parity parity, string serialPort)
        {
            this.SerialCom.BaudRate = baudrate;
            this.SerialCom.DataBits = dataBits;
            this.SerialCom.StopBits = stopBits;
            this.SerialCom.Parity = parity;
            this.SerialCom.PortName = serialPort;
            this.SerialCom.Open();
        }
        public void Receive()
        {
            while (this.RecvLoop)
            {
                this.RecvMessage.RecvMessage = this.SerialCom.ReadLine();
                foreach (var action in this.RecvMessageActions)
                {
                    action(this.RecvMessage);
                }
            }
        }

        public void Send(string message)
        {
            message = message + "\r";
            Console.WriteLine("Sending the following message => {0}", message);
            char[] tx = message.ToCharArray();
            for (int i = 0; i < tx.Length; i++)
            {

                this.SerialCom.Write(tx[i].ToString());
            }
        }

        public void Enable()
        {
            this.RecvLoop = true;
        }

        public void Close()
        {
            this.RecvLoop = false;
            this.SerialCom.Close();

        }
    }

    public class Message
    {
        public string RecvMessage { get; set; }

        public Message()
        {
            this.RecvMessage = "";
        }
    }
}
