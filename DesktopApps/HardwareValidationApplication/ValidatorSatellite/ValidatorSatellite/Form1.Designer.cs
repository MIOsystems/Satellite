
namespace ValidatorSatellite
{
    partial class SatelliteValidator
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.MainTableLayout = new System.Windows.Forms.TableLayoutPanel();
            this.PinTableData = new System.Windows.Forms.DataGridView();
            this.Pin = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Status = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SerialTableLayout = new System.Windows.Forms.TableLayoutPanel();
            this.SerialTableLayoutConfiguration = new System.Windows.Forms.TableLayoutPanel();
            this.ButtonSendSerialUART = new System.Windows.Forms.Button();
            this.ButtonSendSerialRS232 = new System.Windows.Forms.Button();
            this.UserInputSerialRSUART = new System.Windows.Forms.TextBox();
            this.UserInputSerialRS232 = new System.Windows.Forms.TextBox();
            this.ConfigurationComPortLayout = new System.Windows.Forms.FlowLayoutPanel();
            this.SerialPortComboBox = new System.Windows.Forms.ComboBox();
            this.OpenComPortButton = new System.Windows.Forms.Button();
            this.CloseComPortButton = new System.Windows.Forms.Button();
            this.RefreshComPort = new System.Windows.Forms.Button();
            this.UserInputSerialRS422 = new System.Windows.Forms.TextBox();
            this.ButtonSendSerialRS422 = new System.Windows.Forms.Button();
            this.SerialOutput = new System.Windows.Forms.RichTextBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.EthernetStatusReplacement = new System.Windows.Forms.Label();
            this.EthernetConnected = new System.Windows.Forms.Label();
            this.MainTableLayout.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PinTableData)).BeginInit();
            this.SerialTableLayout.SuspendLayout();
            this.SerialTableLayoutConfiguration.SuspendLayout();
            this.ConfigurationComPortLayout.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // MainTableLayout
            // 
            this.MainTableLayout.ColumnCount = 2;
            this.MainTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 35F));
            this.MainTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 65F));
            this.MainTableLayout.Controls.Add(this.PinTableData, 0, 0);
            this.MainTableLayout.Controls.Add(this.SerialTableLayout, 1, 0);
            this.MainTableLayout.Controls.Add(this.tableLayoutPanel1, 0, 1);
            this.MainTableLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MainTableLayout.Location = new System.Drawing.Point(0, 0);
            this.MainTableLayout.Name = "MainTableLayout";
            this.MainTableLayout.RowCount = 2;
            this.MainTableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.MainTableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.MainTableLayout.Size = new System.Drawing.Size(1264, 681);
            this.MainTableLayout.TabIndex = 0;
            // 
            // PinTableData
            // 
            this.PinTableData.AllowUserToAddRows = false;
            this.PinTableData.AllowUserToDeleteRows = false;
            this.PinTableData.BackgroundColor = System.Drawing.Color.White;
            this.PinTableData.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.PinTableData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.PinTableData.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Pin,
            this.Status});
            this.PinTableData.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PinTableData.Location = new System.Drawing.Point(3, 3);
            this.PinTableData.Name = "PinTableData";
            this.PinTableData.ReadOnly = true;
            this.PinTableData.Size = new System.Drawing.Size(436, 650);
            this.PinTableData.TabIndex = 0;
            // 
            // Pin
            // 
            this.Pin.HeaderText = "Label";
            this.Pin.Name = "Pin";
            this.Pin.ReadOnly = true;
            // 
            // Status
            // 
            this.Status.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.Status.HeaderText = "Status";
            this.Status.Name = "Status";
            this.Status.ReadOnly = true;
            // 
            // SerialTableLayout
            // 
            this.SerialTableLayout.ColumnCount = 1;
            this.SerialTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.SerialTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.SerialTableLayout.Controls.Add(this.SerialTableLayoutConfiguration, 0, 1);
            this.SerialTableLayout.Controls.Add(this.SerialOutput, 0, 0);
            this.SerialTableLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SerialTableLayout.Location = new System.Drawing.Point(445, 3);
            this.SerialTableLayout.Name = "SerialTableLayout";
            this.SerialTableLayout.RowCount = 2;
            this.SerialTableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 65F));
            this.SerialTableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 35F));
            this.SerialTableLayout.Size = new System.Drawing.Size(816, 650);
            this.SerialTableLayout.TabIndex = 1;
            // 
            // SerialTableLayoutConfiguration
            // 
            this.SerialTableLayoutConfiguration.ColumnCount = 2;
            this.SerialTableLayoutConfiguration.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.SerialTableLayoutConfiguration.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.SerialTableLayoutConfiguration.Controls.Add(this.ButtonSendSerialUART, 1, 2);
            this.SerialTableLayoutConfiguration.Controls.Add(this.ButtonSendSerialRS232, 1, 1);
            this.SerialTableLayoutConfiguration.Controls.Add(this.UserInputSerialRSUART, 0, 2);
            this.SerialTableLayoutConfiguration.Controls.Add(this.UserInputSerialRS232, 0, 1);
            this.SerialTableLayoutConfiguration.Controls.Add(this.ConfigurationComPortLayout, 1, 3);
            this.SerialTableLayoutConfiguration.Controls.Add(this.UserInputSerialRS422, 0, 0);
            this.SerialTableLayoutConfiguration.Controls.Add(this.ButtonSendSerialRS422, 1, 0);
            this.SerialTableLayoutConfiguration.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SerialTableLayoutConfiguration.Location = new System.Drawing.Point(3, 425);
            this.SerialTableLayoutConfiguration.Name = "SerialTableLayoutConfiguration";
            this.SerialTableLayoutConfiguration.RowCount = 4;
            this.SerialTableLayoutConfiguration.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.SerialTableLayoutConfiguration.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.SerialTableLayoutConfiguration.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.SerialTableLayoutConfiguration.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.SerialTableLayoutConfiguration.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.SerialTableLayoutConfiguration.Size = new System.Drawing.Size(810, 222);
            this.SerialTableLayoutConfiguration.TabIndex = 0;
            // 
            // ButtonSendSerialUART
            // 
            this.ButtonSendSerialUART.Location = new System.Drawing.Point(408, 63);
            this.ButtonSendSerialUART.Name = "ButtonSendSerialUART";
            this.ButtonSendSerialUART.Size = new System.Drawing.Size(150, 23);
            this.ButtonSendSerialUART.TabIndex = 10;
            this.ButtonSendSerialUART.Text = "Send Message over UART";
            this.ButtonSendSerialUART.UseVisualStyleBackColor = true;
            // 
            // ButtonSendSerialRS232
            // 
            this.ButtonSendSerialRS232.Location = new System.Drawing.Point(408, 33);
            this.ButtonSendSerialRS232.Name = "ButtonSendSerialRS232";
            this.ButtonSendSerialRS232.Size = new System.Drawing.Size(150, 23);
            this.ButtonSendSerialRS232.TabIndex = 9;
            this.ButtonSendSerialRS232.Text = "Send Message over RS232";
            this.ButtonSendSerialRS232.UseVisualStyleBackColor = true;
            // 
            // UserInputSerialRSUART
            // 
            this.UserInputSerialRSUART.Dock = System.Windows.Forms.DockStyle.Fill;
            this.UserInputSerialRSUART.Location = new System.Drawing.Point(3, 65);
            this.UserInputSerialRSUART.Margin = new System.Windows.Forms.Padding(3, 5, 3, 3);
            this.UserInputSerialRSUART.MaxLength = 32;
            this.UserInputSerialRSUART.Name = "UserInputSerialRSUART";
            this.UserInputSerialRSUART.Size = new System.Drawing.Size(399, 20);
            this.UserInputSerialRSUART.TabIndex = 8;
            // 
            // UserInputSerialRS232
            // 
            this.UserInputSerialRS232.Dock = System.Windows.Forms.DockStyle.Fill;
            this.UserInputSerialRS232.Location = new System.Drawing.Point(3, 35);
            this.UserInputSerialRS232.Margin = new System.Windows.Forms.Padding(3, 5, 3, 3);
            this.UserInputSerialRS232.MaxLength = 32;
            this.UserInputSerialRS232.Name = "UserInputSerialRS232";
            this.UserInputSerialRS232.Size = new System.Drawing.Size(399, 20);
            this.UserInputSerialRS232.TabIndex = 7;
            // 
            // ConfigurationComPortLayout
            // 
            this.ConfigurationComPortLayout.Controls.Add(this.SerialPortComboBox);
            this.ConfigurationComPortLayout.Controls.Add(this.OpenComPortButton);
            this.ConfigurationComPortLayout.Controls.Add(this.CloseComPortButton);
            this.ConfigurationComPortLayout.Controls.Add(this.RefreshComPort);
            this.ConfigurationComPortLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ConfigurationComPortLayout.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.ConfigurationComPortLayout.Location = new System.Drawing.Point(408, 93);
            this.ConfigurationComPortLayout.Name = "ConfigurationComPortLayout";
            this.ConfigurationComPortLayout.Size = new System.Drawing.Size(399, 126);
            this.ConfigurationComPortLayout.TabIndex = 6;
            // 
            // SerialPortComboBox
            // 
            this.SerialPortComboBox.FormattingEnabled = true;
            this.SerialPortComboBox.Location = new System.Drawing.Point(3, 3);
            this.SerialPortComboBox.Name = "SerialPortComboBox";
            this.SerialPortComboBox.Size = new System.Drawing.Size(150, 21);
            this.SerialPortComboBox.TabIndex = 3;
            // 
            // OpenComPortButton
            // 
            this.OpenComPortButton.Location = new System.Drawing.Point(3, 30);
            this.OpenComPortButton.Name = "OpenComPortButton";
            this.OpenComPortButton.Size = new System.Drawing.Size(150, 23);
            this.OpenComPortButton.TabIndex = 4;
            this.OpenComPortButton.Text = "Open Com Port";
            this.OpenComPortButton.UseVisualStyleBackColor = true;
            this.OpenComPortButton.Click += new System.EventHandler(this.OpenComPortButton_Click_1);
            // 
            // CloseComPortButton
            // 
            this.CloseComPortButton.Location = new System.Drawing.Point(3, 59);
            this.CloseComPortButton.Name = "CloseComPortButton";
            this.CloseComPortButton.Size = new System.Drawing.Size(150, 23);
            this.CloseComPortButton.TabIndex = 6;
            this.CloseComPortButton.Text = "Close Com Port";
            this.CloseComPortButton.UseVisualStyleBackColor = true;
            // 
            // RefreshComPort
            // 
            this.RefreshComPort.Location = new System.Drawing.Point(3, 88);
            this.RefreshComPort.Name = "RefreshComPort";
            this.RefreshComPort.Size = new System.Drawing.Size(150, 23);
            this.RefreshComPort.TabIndex = 5;
            this.RefreshComPort.Text = "Refresh Com Port";
            this.RefreshComPort.UseVisualStyleBackColor = true;
            // 
            // UserInputSerialRS422
            // 
            this.UserInputSerialRS422.Dock = System.Windows.Forms.DockStyle.Fill;
            this.UserInputSerialRS422.Location = new System.Drawing.Point(3, 5);
            this.UserInputSerialRS422.Margin = new System.Windows.Forms.Padding(3, 5, 3, 3);
            this.UserInputSerialRS422.MaxLength = 32;
            this.UserInputSerialRS422.Name = "UserInputSerialRS422";
            this.UserInputSerialRS422.Size = new System.Drawing.Size(399, 20);
            this.UserInputSerialRS422.TabIndex = 0;
            // 
            // ButtonSendSerialRS422
            // 
            this.ButtonSendSerialRS422.Location = new System.Drawing.Point(408, 3);
            this.ButtonSendSerialRS422.Name = "ButtonSendSerialRS422";
            this.ButtonSendSerialRS422.Size = new System.Drawing.Size(150, 23);
            this.ButtonSendSerialRS422.TabIndex = 3;
            this.ButtonSendSerialRS422.Text = "Send Message over RS422";
            this.ButtonSendSerialRS422.UseVisualStyleBackColor = true;
            this.ButtonSendSerialRS422.Click += new System.EventHandler(this.ButtonSendSerial_Click);
            // 
            // SerialOutput
            // 
            this.SerialOutput.AcceptsTab = true;
            this.SerialOutput.BackColor = System.Drawing.Color.White;
            this.SerialOutput.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.SerialOutput.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SerialOutput.Location = new System.Drawing.Point(3, 3);
            this.SerialOutput.MaxLength = 120;
            this.SerialOutput.Name = "SerialOutput";
            this.SerialOutput.ReadOnly = true;
            this.SerialOutput.Size = new System.Drawing.Size(810, 416);
            this.SerialOutput.TabIndex = 1;
            this.SerialOutput.Text = "";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 75F));
            this.tableLayoutPanel1.Controls.Add(this.EthernetStatusReplacement, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.EthernetConnected, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 656);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(442, 25);
            this.tableLayoutPanel1.TabIndex = 2;
            // 
            // EthernetStatusReplacement
            // 
            this.EthernetStatusReplacement.Dock = System.Windows.Forms.DockStyle.Fill;
            this.EthernetStatusReplacement.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EthernetStatusReplacement.Location = new System.Drawing.Point(113, 0);
            this.EthernetStatusReplacement.Name = "EthernetStatusReplacement";
            this.EthernetStatusReplacement.Size = new System.Drawing.Size(326, 25);
            this.EthernetStatusReplacement.TabIndex = 2;
            this.EthernetStatusReplacement.Text = "Not Connected";
            this.EthernetStatusReplacement.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // EthernetConnected
            // 
            this.EthernetConnected.Dock = System.Windows.Forms.DockStyle.Fill;
            this.EthernetConnected.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EthernetConnected.Location = new System.Drawing.Point(3, 0);
            this.EthernetConnected.Name = "EthernetConnected";
            this.EthernetConnected.Size = new System.Drawing.Size(104, 25);
            this.EthernetConnected.TabIndex = 1;
            this.EthernetConnected.Text = "Ethernet Status:";
            this.EthernetConnected.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // SatelliteValidator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 681);
            this.Controls.Add(this.MainTableLayout);
            this.Name = "SatelliteValidator";
            this.Text = "Validate Satellite";
            this.MainTableLayout.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.PinTableData)).EndInit();
            this.SerialTableLayout.ResumeLayout(false);
            this.SerialTableLayoutConfiguration.ResumeLayout(false);
            this.SerialTableLayoutConfiguration.PerformLayout();
            this.ConfigurationComPortLayout.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel MainTableLayout;
        private System.Windows.Forms.DataGridView PinTableData;
        private System.Windows.Forms.DataGridViewTextBoxColumn Pin;
        private System.Windows.Forms.DataGridViewTextBoxColumn Status;
        private System.Windows.Forms.TableLayoutPanel SerialTableLayout;
        private System.Windows.Forms.TableLayoutPanel SerialTableLayoutConfiguration;
        private System.Windows.Forms.RichTextBox SerialOutput;
        private System.Windows.Forms.TextBox UserInputSerialRS422;
        private System.Windows.Forms.Button ButtonSendSerialRS422;
        private System.Windows.Forms.FlowLayoutPanel ConfigurationComPortLayout;
        private System.Windows.Forms.ComboBox SerialPortComboBox;
        private System.Windows.Forms.Button OpenComPortButton;
        private System.Windows.Forms.Button CloseComPortButton;
        private System.Windows.Forms.Button RefreshComPort;
        private System.Windows.Forms.TextBox UserInputSerialRSUART;
        private System.Windows.Forms.TextBox UserInputSerialRS232;
        private System.Windows.Forms.Button ButtonSendSerialUART;
        private System.Windows.Forms.Button ButtonSendSerialRS232;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label EthernetStatusReplacement;
        private System.Windows.Forms.Label EthernetConnected;
    }
}

