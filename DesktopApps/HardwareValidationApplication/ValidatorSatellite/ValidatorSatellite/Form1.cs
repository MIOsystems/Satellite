using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using FormsTimer = System.Windows.Forms;
namespace ValidatorSatellite
{
    public partial class SatelliteValidator : Form
    {
        private Ethernet Ethernet;

        private Serial SerialCommunication;
        private Message SerialMessage;
        private string[] SerialPortNames;
        
        private ValidateModel RecvModel;

        private bool HasNewData;
        private bool HasNewSerialData;

        private Thread EthernetThread;
        private Thread SerialThread;
        private ManualResetEvent SerialEventHandler;
        private FormsTimer.Timer DrawTimer;
        private FormsTimer.Timer SerialTimer;

        private bool ComPortOpen;
        


        public SatelliteValidator()
        {
            InitializeComponent();
            this.Ethernet = new Ethernet();
            this.HasNewData = false;
            this.HasNewSerialData = false;
            this.ComPortOpen = false;
            this.RecvModel = new ValidateModel();
            this.SerialCommunication = new Serial();
            

            this.LoadRecvModel(this.Ethernet);
            this.LoadRecvSerial(this.SerialCommunication);


            
            this.EthernetThread = new Thread(this.Ethernet.Poll);
            this.EthernetThread.IsBackground = true;
            this.EthernetThread.Start();


            this.SerialThread = new Thread(this.SerialCommunication.Receive);
            this.SerialThread.IsBackground = true;



            Populate();

            this.DrawTimer = new FormsTimer.Timer();
            this.DrawTimer.Interval = 100;
            this.DrawTimer.Tick += new EventHandler(DrawData);

            this.SerialTimer = new FormsTimer.Timer();
            this.SerialTimer.Interval = 100;
            this.SerialTimer.Tick += new EventHandler(DrawSerialData);

            this.DrawTimer.Start();
            this.SerialTimer.Start();
        }

        public void LoadRecvSerial(Serial Serial)
        {
            this.SerialCommunication.RecvMessageActions.Add( (Message) =>
            {
                this.SerialMessage = Message;
                this.HasNewSerialData = true;
            });
        }
        public void LoadRecvModel(Ethernet ethernet)
        {
            this.Ethernet.ModelActions.Add((ValidateModel) =>
            {
                this.RecvModel = ValidateModel;
                this.HasNewData = true;
            });
        }


        public void Populate()
        {
            // Table
            this.PinTableData.Rows.Add("DIP 1: ", this.RecvModel.Dip1);
            this.PinTableData.Rows.Add("DIP 2: ", this.RecvModel.Dip2);
            this.PinTableData.Rows.Add("DIP 3: ", this.RecvModel.Dip3);
            this.PinTableData.Rows.Add("DIP 4: ", this.RecvModel.Dip4);

            this.PinTableData.Rows.Add("Digital Output 1: ", this.RecvModel.DigitalOut1);
            this.PinTableData.Rows.Add("Digital Output 2: ", this.RecvModel.DigitalOut2);
            this.PinTableData.Rows.Add("Digital Output 3: ", this.RecvModel.DigitalOut3);
            this.PinTableData.Rows.Add("Digital Output 4: ", this.RecvModel.DigitalOut4);

            this.PinTableData.Rows.Add("Analog Input 1: ", this.RecvModel.AnalogIn1);
            this.PinTableData.Rows.Add("Analog Input 2: ", this.RecvModel.AnalogIn2);
            this.PinTableData.Rows.Add("Analog Input 3: ", this.RecvModel.AnalogIn3);

            this.PinTableData.Rows.Add("Relay Status: ", this.RecvModel.Relay);

            // Combobox
            this.SerialPortNames = SerialPort.GetPortNames();
            this.SerialPortComboBox.DataSource = this.SerialPortNames;

            // Ethernet Status
        }

        public void DrawSerialData(object sender, EventArgs e)
        {

            if (this.HasNewSerialData)
            {
                this.HasNewSerialData = false;
                this.SerialOutput.AppendText(Environment.NewLine + "[" + DateTime.Now + "]\t" + this.SerialMessage.RecvMessage);
            }
            if(this.ComPortOpen)
            {
                this.ButtonSendSerialRS422.Enabled = true;
                this.ButtonSendSerialRS232.Enabled = true;
                this.ButtonSendSerialUART.Enabled = true;
                this.CloseComPortButton.Enabled = true;
            } else
            {
                this.ButtonSendSerialRS422.Enabled = false;
                this.ButtonSendSerialRS232.Enabled = false;
                this.ButtonSendSerialUART.Enabled = false;
                this.CloseComPortButton.Enabled = false;
            }
        }

        public void DrawData(object sender, EventArgs e)
        {
            this.EthernetStatusReplacement.ForeColor = this.Ethernet.Connected ? Color.Green : Color.Red;
            this.EthernetStatusReplacement.Text = this.Ethernet.Connected ? "Connected" : "Not Connected";
            if (this.HasNewData)
            {

                this.HasNewData = false;
                this.PinTableData.Rows[0].SetValues("DIP 1: ", this.RecvModel.Dip1);
                this.PinTableData.Rows[1].SetValues("DIP 2: ", this.RecvModel.Dip2);
                this.PinTableData.Rows[2].SetValues("DIP 3: ", this.RecvModel.Dip3);
                this.PinTableData.Rows[3].SetValues("DIP 4: ", this.RecvModel.Dip4);

                this.PinTableData.Rows[4].SetValues("Digital Output 1: ", this.RecvModel.DigitalOut1);
                this.PinTableData.Rows[5].SetValues("Digital Output 2: ", this.RecvModel.DigitalOut2);
                this.PinTableData.Rows[6].SetValues("Digital Output 3: ", this.RecvModel.DigitalOut3);
                this.PinTableData.Rows[7].SetValues("Digital Output 4: ", this.RecvModel.DigitalOut4);

                this.PinTableData.Rows[8].SetValues("Analog Input 1: ", this.RecvModel.AnalogIn1);
                this.PinTableData.Rows[9].SetValues("Analog Input 2: ", this.RecvModel.AnalogIn2);
                this.PinTableData.Rows[10].SetValues("Analog Input 3: ", this.RecvModel.AnalogIn3);

                this.PinTableData.Rows[11].SetValues("Relay Status: ", this.RecvModel.Relay);
            }
        }

        private void RefreshComPort_Click(object sender, EventArgs e)
        {
            this.SerialPortNames = SerialPort.GetPortNames();
            this.SerialPortComboBox.DataSource = this.SerialPortNames;
        }

        private void ButtonSendSerial_Click(object sender, EventArgs e)
        {
            this.SerialCommunication.Send(UserInputSerialRS422.Text);
        }

        private void CloseComPortButton_Click(object sender, EventArgs e)
        {
            this.ComPortOpen = false;
            this.SerialCommunication.Close();
            this.SerialThread.Abort();
        }

        private void OpenComPortButton_Click_1(object sender, EventArgs e)
        {
            this.SerialCommunication.Init(115200, 8, StopBits.One, Parity.None, this.SerialPortComboBox.SelectedItem.ToString());
            this.SerialCommunication.Enable();


            this.SerialThread.Start();
            this.ComPortOpen = true;
        }
    }
}
