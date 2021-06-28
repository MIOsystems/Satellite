using System;
using System.Text;
using util;

namespace DebugHardwareTool.Model
{
    public struct Vector3f
    {
        public float x {get; set; }
        public float y {get; set; }
        public float z { get; set; }
    }

    public class FFT
    {
        public int N { get; set; }
        public Vector3f[] Out { get; set; }
        public int[] counter;
        public int totalCounter;
        private int[] increment;

        public FFT()
        {
            this.N = 256;
            this.counter = new int[3];
            this.Out = new Vector3f[this.N];
            this.increment = new int[3];
            this.totalCounter = 0;
    }

        public void ConvertBytesObj(byte[] packet)
        {
            // First get the prefix
            string prefix = Encoding.ASCII.GetString(PacketUtil.GetBytes(packet, 0, 7)).Substring(0, 5);
            // When you enter this reset everything
            if (this.totalCounter == 8)
            {
                this.Out = new Vector3f[this.N];
                this.totalCounter = 0;
                this.increment = new int[3];
                this.counter = new int[3];
            }

            // 
            for(int i = 0; i < increment.Length; i++)
            {
                increment[i] = 0 + (this.counter[i] * 250);
            }

            if (prefix == "FFTx,")
            {
                Console.WriteLine("Got new FFT X Packet => {0} ", totalCounter.ToString());
                this.counter[0]++;
            }
            else if (prefix == "FFTy,")
            {
                Console.WriteLine("Got new FFT Y Packet => {0} ", totalCounter.ToString());
                this.counter[1]++;

            }

            // Filling the array
            const int max = (8 + (250 * 4)) - 1;
            for (int i = 8; i < max; i += 4)
            {
                if (prefix == "FFTx,")
                {

                    this.Out[increment[0]].x = BitConverter.ToSingle(PacketUtil.GetBytes(packet, i, i + 4), 0);
                    this.increment[0]++;
                }
                else if (prefix == "FFTy,")
                {

                    this.Out[increment[1]].y = BitConverter.ToSingle(PacketUtil.GetBytes(packet, i, i + 4), 0);
                    this.increment[1]++;
                }
                //else if (prefix == "FFTz,")
                //{
                //    //this.Out[increment[2]].z = BitConverter.ToSingle(PacketUtil.GetBytes(packet, i, i + 4), 0);
                //    increment[2]++;
                //}

            }
            this.totalCounter++;
        }

        public void ConvertBytesObjSmallIncrements(byte[] packet)
        {
            // First get the prefix
            string prefix = Encoding.ASCII.GetString(PacketUtil.GetBytes(packet, 0, 7)).Substring(0, 5);
            if(totalCounter == 1)
            {
                this.totalCounter = 0;
                this.increment = new int[3];
                this.counter = new int[3];
            }

            if (prefix == "FFTx,")
            {
                //Console.WriteLine("Got new FFT X Packet => Total: {0} Counter: {1} {2} {3} Increment: {4} {5} {6}",
                //    totalCounter.ToString(), this.counter[0], this.counter[1], this.counter[2], this.increment[0], this.increment[1], this.increment[2]);
                this.counter[0]++;
            }
            else if (prefix == "FFTy,")
            {
                //Console.WriteLine("Got new FFT Y Packet => Total: {0} Counter: {1} {2} {3} Increment: {4} {5} {6}", 
                //    totalCounter.ToString(), this.counter[0], this.counter[1], this.counter[2], this.increment[0], this.increment[1], this.increment[2]);
                this.counter[1]++;
            }
            else if(prefix == "FFTz,")
            {
                //Console.WriteLine("Got new FFT Z Packet => Total: {0} Counter: {1} {2} {3} Increment: {4} {5} {6}",
                //    totalCounter.ToString(), this.counter[0], this.counter[1], this.counter[2], this.increment[0], this.increment[1], this.increment[2]);
                this.counter[2]++;
            }

            int max = (8 + (this.N * 4)) - 1;
            for (int i = 8; i < max; i += 4)
            {
                if (prefix == "FFTx,")
                {
                    byte[] section = PacketUtil.GetBytes(packet, i, i + 4);
                    float value = BitConverter.ToSingle(section, 0);
                    this.Out[increment[0]].x = value;
                    this.increment[0]++;
                }
                else if (prefix == "FFTy,")
                {
                    byte[] section = PacketUtil.GetBytes(packet, i, i + 4);
                    float value = BitConverter.ToSingle(section, 0);
                    this.Out[increment[1]].y = value;
                    this.increment[1]++;
                }
                else if (prefix == "FFTz,")
                {
                    byte[] section = PacketUtil.GetBytes(packet, i, i + 4);
                    float value = BitConverter.ToSingle(section, 0);
                    this.Out[increment[2]].z = value;
                    this.increment[2]++;
                }
            }
            this.totalCounter++;
        }
    }
}
