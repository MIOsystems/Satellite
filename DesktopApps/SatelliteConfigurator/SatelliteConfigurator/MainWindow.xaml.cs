using ScottPlot;
using ScottPlot.Drawing.Colormaps;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace SatelliteConfigurator
{

    public partial class MainWindow : Window
    {
        private SerialPort serialPort = null;
        private Thread serialPortThread = null;
        private bool threadRunning = false;

        private int imuDataPacketsRecieved = 0;
        private System.Timers.Timer imuDataCounterTimer;

        private enum ReceiveState
        {
            RECEIVING_STARTBYTE_1,
            RECEIVING_STARTBYTE_2,
            RECEIVING_MESSAGE_TYPE,
            RECEIVING_PAYLOAD
        };

        //======== IMU chip select ========

        private enum IMUChip
        {
            ACCELEROMETER = 0x00,
            GYROSCOPE = 0x01
        };

        //======== IMU registers ========

        private enum AccelRegisters
        {
            ACCELEROMETER_RANGE = 0x41,
            ACCELEROMETER_BANDWIDTH = 0x40
        };

        private enum GyroRegisters
        {
            GYROSCOPE_RANGE = 0x0F,
            GYROSCOPE_BANDWIDTH = 0x10
        };

        //======== Register values ========

        private enum AccelRange
        {
            RANGE_2G = 0x00,
            RANGE_4G = 0x01,
            RANGE_8G = 0x02,
            RANGE_16G = 0x03
        };

        private enum AccelBandwidthODR
        {
            BANDWIDTH_ODR_12_5 = 0x05,
            BANDWIDTH_ODR_25 = 0x06,
            BANDWIDTH_ODR_50 = 0x07,
            BANDWIDTH_ODR_100 = 0x08,
            BANDWIDTH_ODR_200 = 0x09,
            BANDWIDTH_ODR_400 = 0x0A,
            BANDWIDTH_ODR_800 = 0x0B,
            BANDWIDTH_ODR_1600 = 0x0C
        };

        private enum AccelBandwidthFilter
        {
            BANDWIDTH_FILTER_OSR4 = 0x00,
            BANDWIDTH_FILTER_OSR2 = 0x01,
            BANDWIDTH_FILTER_NORMAL = 0x02
        };

        private enum GyroRange
        {
            RANGE_2000 = 0x00,
            RANGE_1000 = 0x01,
            RANGE_500 = 0x02,
            RANGE_250 = 0x03,
            RANGE_125 = 0x04
        };

        private enum GyroBandwidth
        {
            BANDWIDTH_2000_532 = 0x00,
            BANDWIDTH_2000_230 = 0x01,
            BANDWIDTH_1000_116 = 0x02,
            BANDWIDTH_400_47 = 0x03,
            BANDWIDTH_200_23 = 0x04,
            BANDWIDTH_100_12 = 0x05,
            BANDWIDTH_200_64 = 0x06,
            BANDWIDTH_100_32 = 0x07
        };

        //==================================

        private struct IMUMessage
        {
            public Int16 accelX;
            public Int16 accelY;
            public Int16 accelZ;
            public Int16 gyroX;
            public Int16 gyroY;
            public Int16 gyroZ;
        };

        private struct AcknowlegdementMessage
        {
            public byte chip;
            public byte registerAddress;
            public byte registerValue;
            public byte ack;
        };

        private enum MessageType
        {
            IMU_DATA = 0,
            ACKNOWLEGDEMENT = 1
        };

        private struct Command
        {
            public byte chip;
            public byte registerAddress;
            public byte registerValue;
        }

        List<string> chips = new List<string>() { "Accelerometer", "Gyro" };

        List<string> accelerometerRegisters = new List<string>() { "Range", "Bandwidth" };
        List<string> gyroRegisters = new List<string>() { "Range", "Bandwidth" };

        List<string> accelerometerRangeValues = new List<string>() { "2G", "4G", "8G", "16G" };
        List<string> accelerometerBandwidthOdrValues = new List<string>() { "12.5", "25", "50", "100", "200", "400", "800", "1600" };
        List<string> accelerometerBandwidthFilterValues = new List<string>() { "OSR4", "OSR2", "Normal" };
        List<string> gyroRangeValues = new List<string>() { "2000", "1000", "500", "250", "125" };
        List<string> gyroBandwidthValues = new List<string>() { "2000_532", "2000_230", "1000_116", "400_47", "200_23", "100_12", "200_64", "100_32" };

        Command command = new Command() {
            chip = (byte)IMUChip.ACCELEROMETER,
            registerAddress = (byte)AccelRegisters.ACCELEROMETER_RANGE,
            registerValue = (byte)AccelRange.RANGE_4G
        };

        IMUDataVisualizer imuDataVisualizer;

        public MainWindow()
        {
            //SerialPort test = new SerialPort(, 115200);
            InitializeComponent();

            this.imuDataVisualizer = new IMUDataVisualizer(50);
            grd_Grid.Children.Add(this.imuDataVisualizer);
            Grid.SetColumn(this.imuDataVisualizer, 2);
            Grid.SetRow(this.imuDataVisualizer, 1);
            Grid.SetColumnSpan(this.imuDataVisualizer, 2);
            Grid.SetRowSpan(this.imuDataVisualizer, 2);

            List<string> portnames = SerialPort.GetPortNames().ToList();

            FillComboBox(portnames, cmb_ComPorts);
            FillComboBox(chips, cmb_Chip);
            FillComboBox(accelerometerRegisters, cmb_Register);
            FillComboBox(accelerometerRangeValues, cmb_Value);

            //double[] dataX = new double[] { 1, 2, 3, 4 };
            //double[] dataY = new double[] { 1, 2, 3, 4 };
            //plt_Graph.Plot.AddScatter(dataX, dataY);
            //plt_Graph.Refresh();

            this.imuDataCounterTimer = new System.Timers.Timer(1000.0);
            this.imuDataCounterTimer.Elapsed += ScanlineCounterTimer_Elapsed;
            this.imuDataCounterTimer.Start();
        }

        private void ScanlineCounterTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            Application.Current.Dispatcher.Invoke(DispatcherPriority.Background, new Action(() =>
            {
                lbl_PacketsPerSecond.Content = this.imuDataPacketsRecieved;
            }));
            this.imuDataPacketsRecieved = 0;
        }

        void FillComboBox(List<string> items, ComboBox combobox)
        {
            combobox.Items.Clear();

            for (int i = 0; i < items.Count; i++)
                combobox.Items.Add(items[i]);

            if (items.Count > 0)
                combobox.SelectedIndex = 0;
        }

        private void btn_OpenPort_Click(object sender, RoutedEventArgs e)
        {
            if(cmb_ComPorts.Items.Count == 0)
            {
                MessageBox.Show("No ports detected");
                return;
            }

            string selectedPortName = cmb_ComPorts.SelectedItem.ToString();
            this.serialPort = new SerialPort(selectedPortName, 460800, Parity.None, 8, StopBits.One);//115200 460800 
            this.serialPort.Open();

            this.serialPortThread = new Thread(SerialPortThreadRun);
            this.serialPortThread.Start();

            btn_OpenPort.IsEnabled = false;
            btn_ClosePort.IsEnabled = true;
            btn_Transmit.IsEnabled = true;

            this.imuDataVisualizer.StartRenderThread();
        }

        private void btn_ClosePort_Click(object sender, RoutedEventArgs e)
        {
            this.threadRunning = false;
            Thread.Sleep(100);
            this.serialPortThread = null;

            this.serialPort.Close();
            this.serialPort = null;

            btn_Transmit.IsEnabled = false;
            btn_ClosePort.IsEnabled = false;
            btn_OpenPort.IsEnabled = true;

            this.imuDataVisualizer.StopRenderThread();
        }

        private void SerialPortThreadRun()
        {
            this.threadRunning = true;

            byte[] buffer = new byte[1] { 0 };
            ReceiveState receiveState = ReceiveState.RECEIVING_STARTBYTE_1;

            byte[] imuBuffer = new byte[12] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            byte[] acknowledgementBuffer = new byte[4] { 0, 0, 0, 0 };
            MessageType currentMessageType = MessageType.IMU_DATA;
            int currentIndex = 0;

            while (this.threadRunning)
            {
                try
                {
                    if (this.serialPort.BytesToRead == 0)
                        continue;

                    int bytesToRead = this.serialPort.BytesToRead;
                    this.serialPort.Read(buffer, 0, 1);

                    switch (receiveState)
                    {
                        case ReceiveState.RECEIVING_STARTBYTE_1:
                            {
                                if (buffer[0] == 0xF0)
                                    receiveState = ReceiveState.RECEIVING_STARTBYTE_2;
                                break;
                            }
                        case ReceiveState.RECEIVING_STARTBYTE_2:
                            {
                                if (buffer[0] == 0x0F)
                                    receiveState = ReceiveState.RECEIVING_MESSAGE_TYPE;
                                else if (buffer[0] != 0xF0)
                                    receiveState = ReceiveState.RECEIVING_STARTBYTE_1;
                                break;
                            }
                        case ReceiveState.RECEIVING_MESSAGE_TYPE:
                            {
                                currentMessageType = (MessageType)buffer[0];
                                receiveState = ReceiveState.RECEIVING_PAYLOAD;
                                break;
                            }
                        case ReceiveState.RECEIVING_PAYLOAD:
                            {
                                if (currentMessageType == MessageType.IMU_DATA)
                                    imuBuffer[currentIndex] = buffer[0];
                                else if (currentMessageType == MessageType.ACKNOWLEGDEMENT)
                                    acknowledgementBuffer[currentIndex] = buffer[0];

                                currentIndex++;

                                if (currentMessageType == MessageType.IMU_DATA && currentIndex == 12)
                                {
                                    IMUDataVisualizer.IMUData imuData = new IMUDataVisualizer.IMUData()
                                    {
                                        accelX = BitConverter.ToInt16(imuBuffer, 0),
                                        accelY = BitConverter.ToInt16(imuBuffer, 2),
                                        accelZ = BitConverter.ToInt16(imuBuffer, 4),
                                        gyroX = BitConverter.ToInt16(imuBuffer, 6),
                                        gyroY = BitConverter.ToInt16(imuBuffer, 8),
                                        gyroZ = BitConverter.ToInt16(imuBuffer, 10)
                                    };

                                    this.imuDataVisualizer.AddImuData(imuData);

                                    //Application.Current.Dispatcher.Invoke(DispatcherPriority.Background, new Action(() =>
                                    //{
                                    //    lbl_accelX.Content = imuData.accelX;
                                    //    lbl_accelY.Content = imuData.accelY;
                                    //    lbl_accelZ.Content = imuData.accelZ;
                                    //    lbl_gyroX.Content = imuData.gyroX;
                                    //    lbl_gyroY.Content = imuData.gyroY;
                                    //    lbl_gyroZ.Content = imuData.gyroZ;
                                    //}));

                                    currentIndex = 0;
                                    receiveState = ReceiveState.RECEIVING_STARTBYTE_1;
                                    this.imuDataPacketsRecieved++;
                                }
                                else if (currentMessageType == MessageType.ACKNOWLEGDEMENT && currentIndex == 4)
                                {
                                    AcknowlegdementMessage acknowlegdementMessage = new AcknowlegdementMessage()
                                    {
                                        chip = acknowledgementBuffer[0],
                                        registerAddress = acknowledgementBuffer[1],
                                        registerValue = acknowledgementBuffer[2],
                                        ack = acknowledgementBuffer[3]
                                    };

                                    Application.Current.Dispatcher.Invoke(DispatcherPriority.Background, new Action(() =>
                                    {
                                        txb_ReceiveLog.Text += "Ack: " + acknowlegdementMessage.chip + " " + acknowlegdementMessage.registerAddress + " " + acknowlegdementMessage.registerValue + " " + acknowlegdementMessage.ack + "\n";
                                        txb_ReceiveLog.ScrollToEnd();
                                    }));

                                    currentIndex = 0;
                                    receiveState = ReceiveState.RECEIVING_STARTBYTE_1;
                                }

                                if (currentIndex > 12)
                                {
                                    currentIndex = 0;
                                    receiveState = ReceiveState.RECEIVING_STARTBYTE_1;
                                }

                                break;
                            }
                    }
                }
                catch(Exception e)
                {
                    Application.Current.Dispatcher.Invoke(DispatcherPriority.Background, new Action(() =>
                    {
                        btn_ClosePort_Click(null, null);
                    }));
                }
            }
        }

        private void btn_Transmit_Click(object sender, RoutedEventArgs e)
        {
            imuDataVisualizer.ResetImuMinMax();

            byte[] bytes = { command.chip, command.registerAddress, command.registerValue };
            this.serialPort.Write(bytes, 0, bytes.Length);

            txb_TransmitLog.Text += "Command: ";
            for (int i = 0; i < bytes.Length; i++)
                txb_TransmitLog.Text += bytes[i] + " ";
            txb_TransmitLog.Text += "\n";

            txb_TransmitLog.ScrollToEnd();
        }

        private void btn_RefreshPorts_Click(object sender, RoutedEventArgs e)
        {
            cmb_ComPorts.Items.Clear();

            List<string> portnames = SerialPort.GetPortNames().ToList();
            for (int i = 0; i < portnames.Count; i++)
                cmb_ComPorts.Items.Add(portnames[i]);

            if (portnames.Count > 0)
                cmb_ComPorts.SelectedIndex = 0;
        }

        private void cmb_Command_Chip_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(cmb_Chip.SelectedIndex == (int)IMUChip.ACCELEROMETER)
            {
                command.chip = (byte)IMUChip.ACCELEROMETER;
                FillComboBox(accelerometerRegisters, cmb_Register);
                FillComboBox(accelerometerRangeValues, cmb_Value);
            }
            else if (cmb_Chip.SelectedIndex == (int)IMUChip.GYROSCOPE)
            {
                command.chip = (byte)IMUChip.GYROSCOPE;
                FillComboBox(gyroRegisters, cmb_Register);
                FillComboBox(gyroRangeValues, cmb_Value);
            }
        }

        private void cmb_Command_Register_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            stk_FilterBandwidth.Visibility = Visibility.Hidden;
            if (cmb_Chip.SelectedIndex == (int)IMUChip.ACCELEROMETER)
            {
                if (cmb_Register.SelectedIndex == 0)
                {
                    command.registerAddress = (byte)AccelRegisters.ACCELEROMETER_RANGE;
                    FillComboBox(accelerometerRangeValues, cmb_Value);
                }
                else if (cmb_Register.SelectedIndex == 1)
                {
                    command.registerAddress = (byte)AccelRegisters.ACCELEROMETER_BANDWIDTH;
                    FillComboBox(accelerometerBandwidthOdrValues, cmb_Value);
                    FillComboBox(accelerometerBandwidthFilterValues, cmb_AccelFilterBandwidth);
                    stk_FilterBandwidth.Visibility = Visibility.Visible;
                }
            }
            else if (cmb_Chip.SelectedIndex == (int)IMUChip.GYROSCOPE)
            {
                if (cmb_Register.SelectedIndex == 0)
                {
                    command.registerAddress = (byte)GyroRegisters.GYROSCOPE_RANGE;
                    FillComboBox(gyroRangeValues, cmb_Value);
                }
                else if (cmb_Register.SelectedIndex == 1)
                {
                    command.registerAddress = (byte)GyroRegisters.GYROSCOPE_BANDWIDTH;
                    FillComboBox(gyroBandwidthValues, cmb_Value);
                }
            }
        }

        private void cmb_Command_Value_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(command.chip == (byte)IMUChip.ACCELEROMETER && command.registerAddress == (byte)AccelRegisters.ACCELEROMETER_BANDWIDTH)
                command.registerValue = (byte)((cmb_AccelFilterBandwidth.SelectedIndex << 4) | (cmb_Value.SelectedIndex + 5));
            else
                command.registerValue = (byte)cmb_Value.SelectedIndex;
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            Environment.Exit(0);
        }
    }
}
