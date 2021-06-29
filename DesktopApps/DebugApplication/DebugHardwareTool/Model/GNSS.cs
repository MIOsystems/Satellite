using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using util;

namespace Sensor
{
    public class GNSS
    {
		public double lon { get; set; }
        public double lat { get; set; }
        public int height_ellipsoid { get; set; }
        public int height_msl { get; set; }
        public int hor_acc { get; set; }
        public int ver_acc { get; set; }
        public int speed { get; set; }
        public int heading { get; set; }
        public int speed_acc { get; set; }
        public int head_acc { get; set; }
        public UInt32 epoch { get; set; }
        public char fix { get; set; }
        public char num_sat { get; set; } 

         public GNSS()
        {
            this.lon = 0;
            this.lat = 0;
            this.height_ellipsoid = 0;
            this.height_msl = 0;
            this.hor_acc = 0;
            this.ver_acc = 0;
            this.speed = 0;
            this.heading = 0;
            this.speed_acc = 0;
            this.head_acc = 0;
            this.epoch = 0;
            this.fix = '0';
            this.num_sat = '0';
        }

        public void CreateObjFromBytes(byte[] packet)
        {
            this.epoch = BitConverter.ToUInt32(PacketUtil.GetBytes(packet, 48, 52), 0);
            this.lon = BitConverter.ToInt32(PacketUtil.GetBytes(packet, 8, 12), 0) / 10000000.0;
            this.lat = BitConverter.ToInt32(PacketUtil.GetBytes(packet, 12, 16), 0) / 10000000.0;
        }
    }
}
