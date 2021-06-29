namespace MathUtility
{
    public class Vector3f
    {
        public float x { get; set; }
        public float y { get; set; }
        public float z { get; set; }

        public Vector3f(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public Vector3f()
        {
            this.x = 0;
            this.y = 0;
            this.z = 0;
        }

    }
}
