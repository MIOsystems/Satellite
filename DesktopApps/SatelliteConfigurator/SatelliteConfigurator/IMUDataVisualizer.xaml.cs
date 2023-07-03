using ScottPlot;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using static SatelliteConfigurator.IMUDataVisualizer;

namespace SatelliteConfigurator
{
    /// <summary>
    /// Interaction logic for IMUDataVisualizer.xaml
    /// </summary>
    public partial class IMUDataVisualizer : UserControl
    {
        public struct IMUData
        {
            public Int16 accelX;
            public Int16 accelY;
            public Int16 accelZ;
            public Int16 gyroX;
            public Int16 gyroY;
            public Int16 gyroZ;
        };

        private LivePlotBuffer livePlotBufferAccelX;
        private LivePlotBuffer livePlotBufferAccelY;
        private LivePlotBuffer livePlotBufferAccelZ;
        private LivePlotBuffer livePlotBufferGyroX;
        private LivePlotBuffer livePlotBufferGyroY;
        private LivePlotBuffer livePlotBufferGyroZ;

        private Thread updateThread;
        private Queue<IMUData> imuDataBuffer;
        private Mutex imuDataBufferMutex;

        private System.Timers.Timer renderTimer;
        private bool updateNeeded;

        IMUData minImu;
        IMUData maxImu;
        bool firstImu = true;

        public IMUDataVisualizer(int measurementsToDisplay)
        {
            InitializeComponent();

            this.livePlotBufferAccelX = new LivePlotBuffer(measurementsToDisplay);
            this.livePlotBufferAccelY = new LivePlotBuffer(measurementsToDisplay);
            this.livePlotBufferAccelZ = new LivePlotBuffer(measurementsToDisplay);
            this.livePlotBufferGyroX = new LivePlotBuffer(measurementsToDisplay);
            this.livePlotBufferGyroY = new LivePlotBuffer(measurementsToDisplay);
            this.livePlotBufferGyroZ = new LivePlotBuffer(measurementsToDisplay);

            AddPlot(plt_GraphAccelX, this.livePlotBufferAccelX);
            AddPlot(plt_GraphAccelY, this.livePlotBufferAccelY);
            AddPlot(plt_GraphAccelZ, this.livePlotBufferAccelZ);
            AddPlot(plt_GraphGyroX, this.livePlotBufferGyroX);
            AddPlot(plt_GraphGyroY, this.livePlotBufferGyroY);
            AddPlot(plt_GraphGyroZ, this.livePlotBufferGyroZ);

            RefreshAndRender();

            ResetImuMinMax();

            plt_GraphAccelX.Plot.XAxis2.Label(label: "Accel X", size: 14, color: System.Drawing.Color.Black, bold: true);
            plt_GraphAccelY.Plot.XAxis2.Label(label: "Accel Y", size: 14, color: System.Drawing.Color.Black, bold: true);
            plt_GraphAccelZ.Plot.XAxis2.Label(label: "Accel Z", size: 14, color: System.Drawing.Color.Black, bold: true);
            plt_GraphGyroX.Plot.XAxis2.Label(label: "Gyro X", size: 14, color: System.Drawing.Color.Black, bold: true);
            plt_GraphGyroY.Plot.XAxis2.Label(label: "Gyro Y", size: 14, color: System.Drawing.Color.Black, bold: true);
            plt_GraphGyroZ.Plot.XAxis2.Label(label: "Gyro Z", size: 14, color: System.Drawing.Color.Black, bold: true);

            this.renderTimer = new System.Timers.Timer(50);
            this.renderTimer.Elapsed += RenderTimer_Elapsed;
            this.imuDataBuffer = new Queue<IMUData>();
            this.imuDataBufferMutex = new Mutex();
            this.updateThread = new Thread(UpdateThreadRun);
            this.updateThread.Start();
        }

        public void ResetImuMinMax()
        {
            this.minImu = new IMUData()
            {
                accelX = 0,
                accelY = 0,
                accelZ = 0,
                gyroX = 0,
                gyroY = 0,
                gyroZ = 0
            };
            this.maxImu = new IMUData()
            {
                accelX = 0,
                accelY = 0,
                accelZ = 0,
                gyroX = 0,
                gyroY = 0,
                gyroZ = 0
            };
        }

        public void StartRenderThread()
        {
            this.renderTimer.Start();
        }

        public void StopRenderThread()
        {
            this.renderTimer.Stop();
        }

        private void RenderTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            RefreshAndRender();
        }

        private void UpdateThreadRun()
        {
            while(true)
            {
                if(this.imuDataBuffer.Count > 0)
                {
                    this.imuDataBufferMutex.WaitOne();
                    IMUData imuData = this.imuDataBuffer.Dequeue();
                    this.imuDataBufferMutex.ReleaseMutex();

                    //// Calculate min/max imu data
                    //if (!this.firstImu)
                    //{
                    //    // Calculate min
                    //    if (imuData.accelX < this.minImu.accelX)
                    //        this.minImu.accelX = imuData.accelX;
                    //    if (imuData.accelY < this.minImu.accelY)
                    //        this.minImu.accelY = imuData.accelY;
                    //    if (imuData.accelZ < this.minImu.accelZ)
                    //        this.minImu.accelZ = imuData.accelZ;

                    //    if (imuData.gyroX < this.minImu.gyroX)
                    //        this.minImu.gyroX = imuData.gyroX;
                    //    if (imuData.gyroY < this.minImu.gyroY)
                    //        this.minImu.gyroY = imuData.gyroY;
                    //    if (imuData.gyroZ < this.minImu.gyroZ)
                    //        this.minImu.gyroZ = imuData.gyroZ;

                    //    // Calculate max
                    //    if (imuData.accelX > this.maxImu.accelX)
                    //        this.maxImu.accelX = imuData.accelX;
                    //    if (imuData.accelY > this.maxImu.accelY)
                    //        this.maxImu.accelY = imuData.accelY;
                    //    if (imuData.accelZ > this.maxImu.accelZ)
                    //        this.maxImu.accelZ = imuData.accelZ;

                    //    if (imuData.gyroX > this.maxImu.gyroX)
                    //        this.maxImu.gyroX = imuData.gyroX;
                    //    if (imuData.gyroY > this.maxImu.gyroY)
                    //        this.maxImu.gyroY = imuData.gyroY;
                    //    if (imuData.gyroZ > this.maxImu.gyroZ)
                    //        this.maxImu.gyroZ = imuData.gyroZ;
                    //}
                    //else
                    //{
                    //    this.minImu = imuData;
                    //    this.maxImu = imuData;

                    //    this.firstImu = false;
                    //}

                    //Application.Current.Dispatcher.Invoke(DispatcherPriority.Background, new Action(() =>
                    //{
                    //    lbl_MinAccel.Content = "Min x: " + this.minImu.accelX + " y: " + this.minImu.accelY + " z: " + this.minImu.accelZ;
                    //    lbl_MaxAccel.Content = "Max x: " + this.maxImu.accelX + " y: " + this.maxImu.accelY + " z: " + this.maxImu.accelZ;
                    //    lbl_MinGyro.Content = "Min x: " + this.minImu.gyroX + " y: " + this.minImu.gyroY + " z: " + this.minImu.gyroZ;
                    //    lbl_MaxGyro.Content = "Max x: " + this.maxImu.gyroX + " y: " + this.maxImu.gyroY + " z: " + this.maxImu.gyroZ;
                    //}));

                    //Console.WriteLine("Min accel (" + "x: " + this.minImu.accelX + " y: " + this.minImu.accelY + " z: " + this.minImu.accelZ + ")");
                    //Console.WriteLine("Max accel (" + "x: " + this.maxImu.accelX + " y: " + this.maxImu.accelY + " z: " + this.maxImu.accelZ + ")");
                    //Console.WriteLine("Min gyro (" + "x: " + this.minImu.gyroX + " y: " + this.minImu.gyroY + " z: " + this.minImu.gyroZ + ")");
                    //Console.WriteLine("Max gyro (" + "x: " + this.maxImu.gyroX + " y: " + this.maxImu.gyroY + " z: " + this.maxImu.gyroZ + ")");

                    // Plot grid points
                    double degToRad = 0.01745329251;
                    double multiplier = degToRad * 1000.0 / 32768.0;

                    this.livePlotBufferAccelX.AddValue((double)imuData.accelX);
                    this.livePlotBufferAccelY.AddValue((double)imuData.accelY);
                    this.livePlotBufferAccelZ.AddValue((double)imuData.accelZ);
                    this.livePlotBufferGyroX.AddValue((double)imuData.gyroX);
                    this.livePlotBufferGyroY.AddValue((double)imuData.gyroY);
                    this.livePlotBufferGyroZ.AddValue((double)imuData.gyroZ);
                }
                else
                    Thread.Sleep(10);
            }
        }

        public void AddImuData(IMUData imuData)
        {
            this.imuDataBufferMutex.WaitOne();
            this.imuDataBuffer.Enqueue(imuData);
            this.imuDataBufferMutex.ReleaseMutex();
        }

        private void AddPlot(WpfPlot wpfPlot, LivePlotBuffer livePlotBuffer)
        {
            wpfPlot.Plot.AxisAuto();
            wpfPlot.Plot.SetInnerViewLimits(0, 50, -30000, 30000);
            //wpfPlot.Plot.SetInnerViewLimits(0, 50, 14000, 18000);
            ScottPlot.Plottable.SignalPlot signalPlot = wpfPlot.Plot.AddSignal(livePlotBuffer.GetBuffer());
            signalPlot.MarkerSize = 0;
            signalPlot.Color = System.Drawing.Color.Black;
            signalPlot.FillAboveAndBelow(System.Drawing.Color.Green, System.Drawing.Color.Transparent, System.Drawing.Color.Transparent, System.Drawing.Color.Red, 1);
            signalPlot.BaselineY = 0;
            //wpfPlot.Plot.AxisScaleLock(true, EqualScaleMode.PreserveX);
            //wpfPlot.Plot.AxisAuto();

            //wpfPlot.Plot.Margins(x: 0);
        }

        private void RefreshAndRender()
        {
            Application.Current.Dispatcher.Invoke(DispatcherPriority.Background, new Action(() =>
            {
                plt_GraphAccelX.Refresh();
                plt_GraphAccelY.Refresh();
                plt_GraphAccelZ.Refresh();
                plt_GraphGyroX.Refresh();
                plt_GraphGyroY.Refresh();
                plt_GraphGyroZ.Refresh();

                plt_GraphAccelX.Render();
                plt_GraphAccelY.Render();
                plt_GraphAccelZ.Render();
                plt_GraphGyroX.Render();
                plt_GraphGyroY.Render();
                plt_GraphGyroZ.Render();
            }));
        }
    }
}
