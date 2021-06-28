using MathUtility;
using System;
using util;

namespace Sensor
{
    public class IMUCustomer
    {
        public Statistic x { get; set; }
        public Statistic y { get; set; }
        public Statistic z { get; set; }
        public Vector3f angle { get; set; }

        public IMUCustomer(Statistic x, Statistic y, Statistic z, Vector3f angle)
        {
            this.x = x ?? throw new ArgumentNullException(nameof(x));
            this.y = y ?? throw new ArgumentNullException(nameof(y));
            this.z = z ?? throw new ArgumentNullException(nameof(z));
            this.angle = angle ?? throw new ArgumentNullException(nameof(angle));
        }

        public IMUCustomer()
        {
            this.x = new Statistic();
            this.y = new Statistic();
            this.z = new Statistic();
            this.angle = new Vector3f();
        }


        /**
         * --------------------------------------------------------------
         * |					IMU UDP PACKET 							|
         * --------------------------------------------------------------
         * |  char		| prefix			|	5 bytes	|	0	|	5	|
         * |			| STRUCT PADDING	| 	3 bytes	|	5	| 	8	|
         * |  f32		| avg_x				|	4 bytes	|	8	|	12	|
         * |  f32		| max_x				|	4 bytes	|	12	|	16	|
         * |  f32		| min_x				|	4 bytes	|	16	|	20	|
         * |  f32		| avg_y				|	4 bytes	|	20	|	24	|
         * |  f32		| max_y				|	4 bytes	|	24	|	28	|
         * |  f32		| min_y				|	4 bytes	|	28	|	32	|
         * |  f32		| avg_z				|	4 bytes	|	32	|	36	|
         * |  f32		| max_z				|	4 bytes	|	36	|	40	|
         * |  f32		| min_z				|	4 bytes	|	40	|	44	|
         * |  f32		| angle_x			|	4 bytes	|	44	|	48	|
         * |  f32		| angle_y			|	4 bytes	|	48	|	52	|
         * |  f32		| angle_z			|	4 bytes	|	52	|	56	|
         * --------------------------------------------------------------
         */
        public void ConvertBytesToOBj(byte[] packet)
        {
            // x
            float avg = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 8,  12), 0);
            float max = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 12, 16), 0);
            float min = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 16, 20), 0);

            this.x = new Statistic(avg, max, min);

            // y
            avg = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 20, 24), 0);
            max = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 24, 28), 0);
            min = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 28, 32), 0);

            this.y = new Statistic(avg, max, min);

            // z
            avg = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 32, 36), 0);
            max = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 36, 40), 0);
            min = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 40, 44), 0);

            this.z = new Statistic(avg, max, min);

            // angle

            float angle_x = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 44, 48), 0);
            float angle_y = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 48, 52), 0);
            float angle_z = BitConverter.ToSingle(PacketUtil.GetBytes(packet, 52, 56), 0);

            this.angle = new Vector3f(angle_x, angle_y, angle_z);
        }

    }
}
