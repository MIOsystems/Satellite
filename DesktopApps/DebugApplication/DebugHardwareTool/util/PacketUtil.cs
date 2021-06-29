using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace util
{
    public class PacketUtil
    {
        public static byte[] GetBytes(byte[] packet, int start, int end)
        {
            int size = end - start;
            byte[] retrieved = new byte[size];
            int counter = 0;

            for (int i = start; i < end; i++)
            {
                retrieved[counter] = packet[i];
                counter++;
            }

            return retrieved;
        }
    }
}
