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

            plt_GraphAccelX.Plot.XAxis2.Label(label: "Accel X", size: 14, color: System.Drawing.Color.Black, bold: true);
            plt_GraphAccelY.Plot.XAxis2.Label(label: "Accel Y", size: 14, color: System.Drawing.Color.Black, bold: true);
            plt_GraphAccelZ.Plot.XAxis2.Label(label: "Accel Z", size: 14, color: System.Drawing.Color.Black, bold: true);
            plt_GraphGyroX.Plot.XAxis2.Label(label: "Gyro X", size: 14, color: System.Drawing.Color.Black, bold: true);
            plt_GraphGyroY.Plot.XAxis2.Label(label: "Gyro Y", size: 14, color: System.Drawing.Color.Black, bold: true);
            plt_GraphGyroZ.Plot.XAxis2.Label(label: "Gyro Z", size: 14, color: System.Drawing.Color.Black, bold: true);

            this.renderTimer = new System.Timers.Timer(25);
            this.renderTimer.Elapsed += RenderTimer_Elapsed;
            this.imuDataBuffer = new Queue<IMUData>();
            this.imuDataBufferMutex = new Mutex();
            this.updateThread = new Thread(UpdateThreadRun);
            this.updateThread.Start();
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
