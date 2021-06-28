using System;
using util;

namespace Sensor
{
    public class ProximitySensor
    {
        public UInt16 Value { get; set; }

        public ProximitySensor(ushort value)
        {
            this.Value = value;
        }

        public ProximitySensor()
        {
            this.Value = 0;
        }

        public void ConvertBytesToObj(byte[] packet)
        {
            this.Value = BitConverter.ToUInt16(PacketUtil.GetBytes(packet, 8, 10), 0);
        }
    }
}
