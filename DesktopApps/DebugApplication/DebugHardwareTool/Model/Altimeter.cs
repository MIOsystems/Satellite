using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using util;

namespace Sensor
{
    public class Altimeter
    { 

        public int Distance { get; set; }
        public int Sum { get; set; }
        public int Counter { get; set; }


        public Altimeter()
        {
            this.Distance = 0;
            this.Sum = 0;
            this.Counter = 0;
        }

        public void ConvertBytesToOBj(byte[] packet)
        {
            this.Distance = BitConverter.ToInt32(PacketUtil.GetBytes(packet, 8, 12), 0);
            this.Sum = BitConverter.ToInt32(PacketUtil.GetBytes(packet, 12, 16), 0);
            this.Counter = BitConverter.ToInt32(PacketUtil.GetBytes(packet, 16, 20), 0);
        }
    }
}
