using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ValidatorSatellite
{
    public class Ethernet
    {
        public UdpClient Client;
        public IPEndPoint RemoteEndPoint;
        private const int PORT = 62510;
        private byte[] Packet;

        public List<Action<ValidateModel>> ModelActions;
        public ValidateModel RecvModel;
        public bool Connected { get; set; }

        public Ethernet()
        {
            this.Client = new UdpClient(PORT);
            this.RemoteEndPoint = new IPEndPoint(IPAddress.Any, PORT);

            this.ModelActions = new List<Action<ValidateModel>>();
            this.RecvModel = new ValidateModel();
            this.Connected = false;

        }

        public void Poll()
        {
            while(true)
            {
                Console.WriteLine("Starting Poll Ethernet");
                this.Packet = this.Client.Receive(ref this.RemoteEndPoint);
                if(Packet != null && Packet.Length > 0)
                {
                    this.Connected = true;
                    this.RecvModel.createFromByte(Encoding.ASCII.GetString(Packet));
                    foreach(var action in this.ModelActions)
                    {
                        action(this.RecvModel);
                    }
                }
            }
        }
    }
}
