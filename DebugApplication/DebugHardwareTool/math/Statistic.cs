namespace MathUtility
{
    public class Statistic
    {
        public float avg { get; set;}
        public float max { get; set;}
        public float min { get; set;}

        public Statistic(float avg, float max, float min)
        {
            this.avg = avg;
            this.max = max;
            this.min = min;
        }

        public Statistic()
        {
            this.avg = 0;
            this.max = 0;
            this.min = 0;
        }
    }
}
