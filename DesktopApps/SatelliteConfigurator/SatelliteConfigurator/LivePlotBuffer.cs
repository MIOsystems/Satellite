using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SatelliteConfigurator
{
    public class LivePlotBuffer
    {
        private double[] buffer;

        public LivePlotBuffer(int bufferSize)
        {
            this.buffer = new double[bufferSize];
            for (int i = 0; i < bufferSize; i++)
                this.buffer[i] = 0;
        }

        public void AddValue(double value)
        {
            for (int i = 0; i < (this.buffer.Length - 1); i++)
                this.buffer[i] = this.buffer[i + 1];
            this.buffer[this.buffer.Length - 1] = value;
        }

        public double[] GetBuffer()
        {
            return this.buffer;
        }
    }
}
