using Commmunication;
using DebugHardwareTool.Model;
using GMap.NET;
using GMap.NET.MapProviders;
using Sensor;
using System;
using System.Globalization;
using System.IO;
using System.Threading;
using System.Windows.Forms;
using formsTimer = System.Windows.Forms;

namespace DebugHardwareTool
{
    public partial class MainView : Form
    {
        private readonly UDP Ethernet;
        private readonly Thread EthernetRecvThread;

        private IMUCustomer CustomerIMU;
        private InertialMeasurementUnit ImuDebugData;
        private ProximitySensor ProximitySensor;
        private Altimeter Altimeter;
        private FFT FFTData;
        private GNSS GNSSData;
        private int counter;

        public bool NewGNSSData { get; private set; }

        private readonly formsTimer.Timer GraphsFpsTimer = new formsTimer.Timer();
        private readonly formsTimer.Timer DataFpsTimer = new formsTimer.Timer();
        private bool NewDebugImuData;
        private bool NewCustomerData;
        private bool NewProximitySensorData;
        private bool NewAltimeterData;
        private bool NewFFTData;

        public MainView()
        {
            InitializeComponent();
            this.ImuDebugData = new InertialMeasurementUnit();
            this.CustomerIMU = new IMUCustomer();
            this.Altimeter = new Altimeter();
            this.Ethernet = new UDP();
            this.FFTData = new FFT();
            this.GNSSData = new GNSS();
            this.NewDebugImuData = false;
            this.NewCustomerData = false;
            this.NewProximitySensorData = false;
            this.NewAltimeterData = false;
            this.NewFFTData = false;
            counter = 0;

            loadDebugIMU(this.Ethernet);
            loadCustomerData(this.Ethernet);
            LoadProximitySensor(this.Ethernet);
            LoadAltimeterData(this.Ethernet);
            LoadFFTData(this.Ethernet);
            LoadGNSSData(this.Ethernet);
            this.EthernetRecvThread = new Thread(this.Ethernet.Start);
            this.EthernetRecvThread.IsBackground = true;
            this.EthernetRecvThread.Start();

            DataFpsTimer.Interval = 500;
            DataFpsTimer.Tick += new EventHandler(dataFpsTick);
            GraphsFpsTimer.Interval = 1;
            GraphsFpsTimer.Tick += new EventHandler(graphFpsTick);
            GraphsFpsTimer.Start();
            DataFpsTimer.Start();



            this.fftChart.ChartAreas["ChartArea1"].AxisX.Maximum = this.FFTData.N;
            CreateMap();
        }


        public void CreateMap()
        {
            GNSSMapControl.MapProvider = GMapProviders.GoogleMap;
            GNSSMapControl.Position = new PointLatLng(51.652490, 4.859457);
            GNSSMapControl.MinZoom = 0;
            GNSSMapControl.MaxZoom = 24;
            GNSSMapControl.Zoom = 20;
        }

        private void graphFpsTick(object sender, EventArgs e)
        {
            if (this.NewDebugImuData)
            {
                this.UpdateIMUGraph();
                this.NewDebugImuData = false;
            }
            else if (this.NewCustomerData)
            {
                counter++;
                UpdateGNSSData();
                this.updateCustomerGraph();
                this.NewCustomerData = false;
            }
            else if (this.NewProximitySensorData)
            {
                this.UpdateProximitySensorData();
                this.NewProximitySensorData = false;
            }
            else if (this.NewAltimeterData)
            {
                this.UpdateAltimeterData();
                this.NewAltimeterData = false;
            }
            else if (this.NewFFTData)
            {
                this.UpdateFFTData();
                this.NewFFTData = false;
            }
            else if (this.NewGNSSData)
            {

                this.UpdateGNSSData();
                this.NewGNSSData = false;


            }
        }

        private void UpdateGNSSData()
        {
            this.GNSSMapControl.Position = new PointLatLng(this.GNSSData.lon, this.GNSSData.lat);
            this.GNSSEpoch.Text = "Packet counter: " + counter;
        }

        private void dataFpsTick(object sender, EventArgs e)
        {
            if (this.NewDebugImuData)
            {
                UpdateIMUListView();
                this.NewDebugImuData = false;
            }

        }

        private void LoadGNSSData(UDP Ethernet)
        {
            Ethernet.GNSSActions.Add((GNSS) =>
            {
                this.GNSSData = GNSS;
                this.NewGNSSData = true;
            });

        }
        private void LoadFFTData(UDP ethernet)
        {
            ethernet.FFTActions.Add((FFT) =>
            {
                this.FFTData = FFT;
                this.NewFFTData = true;
            });
        }

        public void loadCustomerData(UDP ethernet)
        {
            ethernet.CustomerActions.Add((IMUCustomer) =>
            {
                this.CustomerIMU = IMUCustomer;
                this.NewCustomerData = true;
            });
        }

        public void LoadAltimeterData(UDP ethernet)
        {
            ethernet.AltimeterActions.Add((Altimeter) =>
            {
                this.Altimeter = Altimeter;
                this.NewAltimeterData = true;
            });
        }

        public void loadDebugIMU(UDP ethernet)
        {
            ethernet.ImuActions.Add((InertialMeasurementUnit) =>
            {
                this.ImuDebugData = InertialMeasurementUnit;
                this.NewDebugImuData = true;
            });
        }

        public void LoadProximitySensor(UDP ethernet)
        {
            ethernet.ProximityActions.Add((ProximitySensor) =>
            {
                this.ProximitySensor = ProximitySensor;
                this.NewProximitySensorData = true;
            });
        }

        public void UpdateIMUListView()
        {

            this.ListViewIMUData.Items[0].Text = "Ax: " + Math.Round(this.ImuDebugData.ax, 2).ToString("0.##") + " ms^2";
            this.ListViewIMUData.Items[1].Text = "Ay: " + Math.Round(this.ImuDebugData.ay, 2).ToString("0.##") + " ms^2";
            this.ListViewIMUData.Items[2].Text = "Az: " + Math.Round(this.ImuDebugData.az, 2).ToString("0.##") + " ms^2";

            this.ListViewIMUData.Items[3].Text = "Gx: " + Math.Round(this.ImuDebugData.gx, 2).ToString("0.##") + " deg/s";
            this.ListViewIMUData.Items[4].Text = "Gy: " + Math.Round(this.ImuDebugData.gy, 2).ToString("0.##") + " deg/s";
            this.ListViewIMUData.Items[5].Text = "Gz: " + Math.Round(this.ImuDebugData.gz, 2).ToString("0.##") + " deg/s";


            this.ListViewIMUData.Items[6].Text = "Angle x: " + Math.Round(this.ImuDebugData.angle.x, 2) + " deg";
            this.ListViewIMUData.Items[7].Text = "Angle y: " + Math.Round(this.ImuDebugData.angle.y, 2) + " deg";
            this.ListViewIMUData.Items[8].Text = "Angle z: " + Math.Round(this.ImuDebugData.angle.z, 2) + " deg";

            this.circleAnglePicker1.Value = Convert.ToInt32(this.ImuDebugData.angle.x) + 90;
            this.circleAnglePicker2.Value = Convert.ToInt32(this.ImuDebugData.angle.y) + 90;
            this.circleAnglePicker3.Value = Convert.ToInt32(this.ImuDebugData.angle.z) + 90;
        }

        public void updateCustomerGraph()
        {
            this.StatisticCustomerImu.Series["Statistic"].Points.Clear();
            this.StatisticCustomerImu.Series["avg"].Points.Clear();
            this.StatisticCustomerImu.Series["Statistic"].Points.AddXY(0, 0, this.CustomerIMU.x.min, this.CustomerIMU.x.max);
            this.StatisticCustomerImu.Series["Statistic"].Points.AddXY(1, 0, this.CustomerIMU.y.min, this.CustomerIMU.y.max);
            this.StatisticCustomerImu.Series["Statistic"].Points.AddXY(2, 0, this.CustomerIMU.z.min, this.CustomerIMU.z.max);

            this.StatisticCustomerImu.Series["avg"].Points.AddXY(0, 0, this.CustomerIMU.x.avg, this.CustomerIMU.x.avg);
            this.StatisticCustomerImu.Series["avg"].Points.AddXY(1, 0, this.CustomerIMU.y.avg, this.CustomerIMU.y.avg);
            this.StatisticCustomerImu.Series["avg"].Points.AddXY(2, 0, this.CustomerIMU.z.avg, this.CustomerIMU.z.avg);
            this.StatisticCustomerImu.Refresh();
        }

        private void UpdateProximitySensorData()
        {
            this.ProximityValue.Text = this.ProximitySensor.Value.ToString();
        }

        private void UpdateAltimeterData()
        {
            this.AltimeterValue.Text = (this.Altimeter.Distance).ToString();
        }

        private void UpdateFFTData()
        {

            if (this.FFTData.totalCounter == 1)
            {
                this.fftChart.Series["X"].Points.Clear();
                this.fftChart.Series["Y"].Points.Clear();
                this.fftChart.Series["Z"].Points.Clear();
                for (int i = 0; i < this.FFTData.N; i++)
                {
                    this.fftChart.Series["X"].Points.AddY(this.FFTData.Out[i].x);
                    this.fftChart.Series["Y"].Points.AddY(this.FFTData.Out[i].y);
                    this.fftChart.Series["Z"].Points.AddY(this.FFTData.Out[i].z);
                }
            }
        }


        public void UpdateIMUGraph()
        {
            this.chartAccel.Series["Ax"].Points.AddXY(this.Ethernet.t, this.ImuDebugData.ax);
            this.chartAccel.Series["Ay"].Points.AddXY(this.Ethernet.t, this.ImuDebugData.ay);
            this.chartAccel.Series["Az"].Points.AddXY(this.Ethernet.t, this.ImuDebugData.az);
            this.chartGyro.Series["Gx"].Points.AddXY(this.Ethernet.t, this.ImuDebugData.gx);
            this.chartGyro.Series["Gy"].Points.AddXY(this.Ethernet.t, this.ImuDebugData.gy);
            this.chartGyro.Series["Gz"].Points.AddXY(this.Ethernet.t, this.ImuDebugData.gz);
            this.chartAHRS.Series["AngleX"].Points.AddXY(this.Ethernet.t, this.ImuDebugData.angle.x);
            this.chartAHRS.Series["AngleY"].Points.AddXY(this.Ethernet.t, this.ImuDebugData.angle.y);
            this.chartAHRS.Series["AngleZ"].Points.AddXY(this.Ethernet.t, this.ImuDebugData.angle.z);

            if (this.chartAccel.Series["Ax"].Points.Count > 100)
            {
                this.chartAccel.Series["Ax"].Points.RemoveAt(0);
                this.chartAccel.Series["Ay"].Points.RemoveAt(0);
                this.chartAccel.Series["Az"].Points.RemoveAt(0);

                this.chartGyro.Series["Gx"].Points.RemoveAt(0);
                this.chartGyro.Series["Gy"].Points.RemoveAt(0);
                this.chartGyro.Series["Gz"].Points.RemoveAt(0);

                this.chartAHRS.Series["AngleX"].Points.RemoveAt(0);
                this.chartAHRS.Series["AngleY"].Points.RemoveAt(0);
                this.chartAHRS.Series["AngleZ"].Points.RemoveAt(0);
            }
            this.chartAccel.Refresh();
            this.chartGyro.Refresh();
            this.chartAHRS.Refresh();
        }
    }
}