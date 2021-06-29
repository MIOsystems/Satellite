using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ValidatorSatellite
{
    public class ValidateModel
    {
        public string Dip1 { get; set; }
        public string Dip2 { get; set; }
        public string Dip3 { get; set; }
        public string Dip4 { get; set; }

        public string DigitalOut1 { get; set; }
        public string DigitalOut2 { get; set; }
        public string DigitalOut3 { get; set; }
        public string DigitalOut4 { get; set; }

        public string AnalogIn1 { get; set; }
        public string AnalogIn2 { get; set; }
        public string AnalogIn3 { get; set; }

        public string Relay { get; set; }
        public ValidateModel()
        {
            this.Dip1 = "";
            this.Dip2 = "";
            this.Dip3 = "";
            this.Dip4 = "";
            this.DigitalOut1 = "";
            this.DigitalOut2 = "";
            this.DigitalOut3 = "";
            this.DigitalOut4 = "";
            this.AnalogIn1 = "";
            this.AnalogIn2 = "";
            this.AnalogIn3 = "";
            this.Relay = "";
        }

        public void createFromByte(string packet)
        {
            string[] pack = packet.Split(',');
            this.Dip1 = pack[0];
            this.Dip2 = pack[1];
            this.Dip3 = pack[2];
            this.Dip4 = pack[3];


            this.DigitalOut1 = pack[4];
            this.DigitalOut2 = pack[5];
            this.DigitalOut3 = pack[6];
            this.DigitalOut4 = pack[7];



            this.AnalogIn1 = pack[8];
            this.AnalogIn2 = pack[9];
            this.AnalogIn3 = pack[10];

            this.Relay = pack[11];
        }
    }
}
