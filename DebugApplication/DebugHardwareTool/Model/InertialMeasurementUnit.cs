using MathUtility;
using System;
using util;

namespace Sensor
{
    public class InertialMeasurementUnit
    {
        public float ax { get; set; }
        public float ay { get; set; }
        public float az { get; set; }
        public float gx { get; set; }
        public float gy { get; set; }
        public float gz { get; set; }
        public Vector3f angle { get; set; }



        public InertialMeasurementUnit(float ax, float ay, float az, float gx, float gy, float gz, Vector3f madgwickAhrs)
        {
            this.ax = ax;
            this.ay = ay;
            this.az = az;
            this.gx = gx;
            this.gy = gy;
            this.gz = gz;
            this.angle = madgwickAhrs ?? throw new ArgumentNullException(nameof(madgwickAhrs));
        }

        public InertialMeasurementUnit()
        {
            this.ax = 0;
            this.ay = 0;
            this.az = 0;
            this.gx = 0;
            this.gy = 0;
            this.gz = 0;
            this.angle = new Vector3f();
        }





        /// <summary>
        /// ---------------------------------------------
        /// |        IMU DATA UDP PACKET                |
        /// ---------------------------------------------
        /// | f32 | Ax		    | 4 bytes | 0   | 4     |
        /// | f32 | Ay		    | 4 bytes | 4   | 8     |
        /// | f32 | Az		    | 4 bytes | 8   | 12    |
        /// | f32 | Gz		    | 4 bytes | 12  | 16    |
        /// | f32 | Gy		    | 4 bytes | 16  | 20    |
        /// | f32 | Gz		    | 4 bytes | 20  | 24    |
        /// | f32 | AngleX	    | 4 bytes | 24  | 28    |
        /// | f32 | AngleY	    | 4 bytes | 28  | 32    |
        /// | f32 | AngleZ	    | 4 bytes | 32  | 36    |
        /// | f32 | CompAngleX	| 4 bytes | 40  | 44    |
        /// | f32 | CompAngleY	| 4 bytes | 44  | 48    |
        /// | f32 | CompAngleZ	| 4 bytes | 48  | 52    |
        /// ---------------------------------------------
        /// </summary>
        public void ConvertBytesToObj(byte[] packet)
        {
            this.ax = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 0, 4), 0);
            this.ay = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 4, 8), 0);
            this.az = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 8, 12), 0);
            this.gx = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 12, 16), 0);
            this.gy = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 16, 20), 0);
            this.gz = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 20, 24), 0);

            this.angle.x = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 24, 28), 0);
            this.angle.y = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 28, 32), 0);
            this.angle.z = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 32, 36), 0);
        }

        public override string ToString()
        {
            return "Ax: " + this.ax + " Ay: " + this.ay + " Az: " + this.az + 
                    " Gx: " + this.gx + " Gy: " + this.gy + " Gz: " + this.gz +
                    "x: " + this.angle.x + " y: " + this.angle.y + " z: " + this.angle.z;
        }
    }
}
