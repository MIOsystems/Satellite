using DebugHardwareTool.Model;
using Sensor;
using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Commmunication
{

    public class UDP
    {
        public UdpClient Client;
        public IPEndPoint RemoteEndPoint;
        private const int PORT = 62510;
        private byte[] packet;
        private string ascii;

        public bool messageReceived;
        public float t { get; set; }
        public List<Action<InertialMeasurementUnit>> ImuActions;
        public List<Action<IMUCustomer>> CustomerActions;
        public List<Action<ProximitySensor>> ProximityActions;
        public List<Action<Altimeter>> AltimeterActions;
        public List<Action<FFT>> FFTActions;
        public List<Action<GNSS>> GNSSActions;

        public InertialMeasurementUnit DebugImu;
        public IMUCustomer Customer;
        public ProximitySensor ProximitySensor;
        public Altimeter AltimeterSensor;
        public FFT fft;
        public GNSS Gnss;

        public UDP()
        {
            this.Client = new UdpClient(PORT);
            this.RemoteEndPoint = new IPEndPoint(IPAddress.Any, PORT);
            this.ImuActions = new List<Action<InertialMeasurementUnit>>();
            this.CustomerActions = new List<Action<IMUCustomer>>();
            this.ProximityActions = new List<Action<ProximitySensor>>();
            this.AltimeterActions = new List<Action<Altimeter>>();
            this.FFTActions = new List<Action<FFT>>();
            this.GNSSActions = new List<Action<GNSS>>();

            this.t = 0;
            this.messageReceived = false;
            this.DebugImu = new InertialMeasurementUnit();
            this.Customer = new IMUCustomer();
            this.ProximitySensor = new ProximitySensor();
            this.AltimeterSensor = new Altimeter();
            this.fft = new FFT();
            this.Gnss = new GNSS();
        }

        public void Start()
        {
            while (true)
            {
                this.packet = this.Client.Receive(ref this.RemoteEndPoint);
                if(packet != null)
                {
                    this.ascii = Encoding.ASCII.GetString(this.packet);
                    if(this.ascii.StartsWith("imu,"))
                    {
                        this.Customer.ConvertBytesToOBj(this.packet);
                        foreach (var action in this.CustomerActions)
                        {
                            action(this.Customer);
                        }
                    }
                    else if (this.ascii.StartsWith("prox,"))
                    {
                        this.ProximitySensor.ConvertBytesToObj(this.packet);
                        foreach(var action in this.ProximityActions)
                        {
                            action(this.ProximitySensor);
                        }
                    }
                    else if(this.ascii.StartsWith("alti,"))
                    {
                        this.AltimeterSensor.ConvertBytesToOBj(this.packet);
                        foreach (var action in this.AltimeterActions)
                        {
                            action(this.AltimeterSensor);
                        }
                    }
                    else if(this.ascii.StartsWith("FFTx,") || this.ascii.StartsWith("FFTy,") || this.ascii.StartsWith("FFTz,"))
                    {
                        this.fft.ConvertBytesObjSmallIncrements(this.packet);
                        foreach (var action in this.FFTActions)
                        {
                            action(this.fft);
                        }
                    }
                    else if(this.ascii.StartsWith("gnss,"))
                    {
                       
                        this.Gnss.CreateObjFromBytes(this.packet);
                        foreach(var action in this.GNSSActions)
                        {
                            action(this.Gnss);
                        }
                    }
                    else
                    {
                        DebugImu.ConvertBytesToObj(packet);
                        foreach (var action in ImuActions)
                        {
                            action(DebugImu);
                        }
                    }

                }   
            }
        }
    }
}
