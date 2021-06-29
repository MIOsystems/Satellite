
namespace DebugHardwareTool
{
    public partial class MainView
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Title title1 = new System.Windows.Forms.DataVisualization.Charting.Title();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series5 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series6 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Title title2 = new System.Windows.Forms.DataVisualization.Charting.Title();
            System.Windows.Forms.ListViewItem listViewItem1 = new System.Windows.Forms.ListViewItem("Ax:");
            System.Windows.Forms.ListViewItem listViewItem2 = new System.Windows.Forms.ListViewItem("Ay:");
            System.Windows.Forms.ListViewItem listViewItem3 = new System.Windows.Forms.ListViewItem("Az:");
            System.Windows.Forms.ListViewItem listViewItem4 = new System.Windows.Forms.ListViewItem("Gx:");
            System.Windows.Forms.ListViewItem listViewItem5 = new System.Windows.Forms.ListViewItem("Gy:");
            System.Windows.Forms.ListViewItem listViewItem6 = new System.Windows.Forms.ListViewItem("Gz:");
            System.Windows.Forms.ListViewItem listViewItem7 = new System.Windows.Forms.ListViewItem("Angle x:");
            System.Windows.Forms.ListViewItem listViewItem8 = new System.Windows.Forms.ListViewItem("Angle y:");
            System.Windows.Forms.ListViewItem listViewItem9 = new System.Windows.Forms.ListViewItem("Angle z:");
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series7 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series8 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series9 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series10 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series11 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series12 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Title title3 = new System.Windows.Forms.DataVisualization.Charting.Title();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea4 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series13 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series14 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Title title4 = new System.Windows.Forms.DataVisualization.Charting.Title();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea5 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend4 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series15 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series16 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series17 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.AltimerTab = new System.Windows.Forms.TabControl();
            this.DebugIMU = new System.Windows.Forms.TabPage();
            this.MainLayout = new System.Windows.Forms.TableLayoutPanel();
            this.leftColumn = new System.Windows.Forms.TableLayoutPanel();
            this.chartGyro = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.chartAccel = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.ListViewIMUData = new System.Windows.Forms.ListView();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.chartAHRS = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.circleAnglePicker1 = new System.Windows.Forms.CircleAnglePicker();
            this.circleAnglePicker2 = new System.Windows.Forms.CircleAnglePicker();
            this.circleAnglePicker3 = new System.Windows.Forms.CircleAnglePicker();
            this.CIMUDEBUG = new System.Windows.Forms.TabPage();
            this.customerIMUMainLayout = new System.Windows.Forms.TableLayoutPanel();
            this.customerIMUGraphView = new System.Windows.Forms.TableLayoutPanel();
            this.StatisticCustomerImu = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.flowLayoutPanel2 = new System.Windows.Forms.FlowLayoutPanel();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.ProximitySwitchMainLayout = new System.Windows.Forms.TableLayoutPanel();
            this.ProximityValue = new System.Windows.Forms.Label();
            this.ProximitySwitch = new System.Windows.Forms.Label();
            this.AltimerData = new System.Windows.Forms.TabPage();
            this.AltimeterLayout = new System.Windows.Forms.TableLayoutPanel();
            this.AltimeterValue = new System.Windows.Forms.Label();
            this.AltimeterPrefix = new System.Windows.Forms.Label();
            this.FFTTabPage = new System.Windows.Forms.TabPage();
            this.fftChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.GNSSTab = new System.Windows.Forms.TabPage();
            this.GNSSLayout = new System.Windows.Forms.TableLayoutPanel();
            this.GNSSMapControl = new GMap.NET.WindowsForms.GMapControl();
            this.GNSSEpoch = new System.Windows.Forms.Label();
            this.AltimerTab.SuspendLayout();
            this.DebugIMU.SuspendLayout();
            this.MainLayout.SuspendLayout();
            this.leftColumn.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chartGyro)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chartAccel)).BeginInit();
            this.tableLayoutPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chartAHRS)).BeginInit();
            this.flowLayoutPanel1.SuspendLayout();
            this.CIMUDEBUG.SuspendLayout();
            this.customerIMUMainLayout.SuspendLayout();
            this.customerIMUGraphView.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.StatisticCustomerImu)).BeginInit();
            this.tabPage1.SuspendLayout();
            this.ProximitySwitchMainLayout.SuspendLayout();
            this.AltimerData.SuspendLayout();
            this.AltimeterLayout.SuspendLayout();
            this.FFTTabPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fftChart)).BeginInit();
            this.GNSSTab.SuspendLayout();
            this.GNSSLayout.SuspendLayout();
            this.SuspendLayout();
            // 
            // AltimerTab
            // 
            this.AltimerTab.Controls.Add(this.DebugIMU);
            this.AltimerTab.Controls.Add(this.CIMUDEBUG);
            this.AltimerTab.Controls.Add(this.tabPage1);
            this.AltimerTab.Controls.Add(this.AltimerData);
            this.AltimerTab.Controls.Add(this.FFTTabPage);
            this.AltimerTab.Controls.Add(this.GNSSTab);
            this.AltimerTab.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AltimerTab.Location = new System.Drawing.Point(0, 0);
            this.AltimerTab.Margin = new System.Windows.Forms.Padding(0);
            this.AltimerTab.Name = "AltimerTab";
            this.AltimerTab.SelectedIndex = 0;
            this.AltimerTab.Size = new System.Drawing.Size(1264, 681);
            this.AltimerTab.TabIndex = 0;
            // 
            // DebugIMU
            // 
            this.DebugIMU.Controls.Add(this.MainLayout);
            this.DebugIMU.Location = new System.Drawing.Point(4, 22);
            this.DebugIMU.Name = "DebugIMU";
            this.DebugIMU.Padding = new System.Windows.Forms.Padding(3);
            this.DebugIMU.Size = new System.Drawing.Size(1256, 655);
            this.DebugIMU.TabIndex = 0;
            this.DebugIMU.Text = "IMU Debug";
            this.DebugIMU.UseVisualStyleBackColor = true;
            // 
            // MainLayout
            // 
            this.MainLayout.ColumnCount = 3;
            this.MainLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 42.85714F));
            this.MainLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 42.85714F));
            this.MainLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 14.28571F));
            this.MainLayout.Controls.Add(this.leftColumn, 0, 0);
            this.MainLayout.Controls.Add(this.ListViewIMUData, 2, 0);
            this.MainLayout.Controls.Add(this.tableLayoutPanel2, 1, 0);
            this.MainLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MainLayout.Location = new System.Drawing.Point(3, 3);
            this.MainLayout.Name = "MainLayout";
            this.MainLayout.RowCount = 1;
            this.MainLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.MainLayout.Size = new System.Drawing.Size(1250, 649);
            this.MainLayout.TabIndex = 1;
            // 
            // leftColumn
            // 
            this.leftColumn.ColumnCount = 1;
            this.leftColumn.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.leftColumn.Controls.Add(this.chartGyro, 0, 1);
            this.leftColumn.Controls.Add(this.chartAccel, 0, 0);
            this.leftColumn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.leftColumn.Location = new System.Drawing.Point(3, 3);
            this.leftColumn.Name = "leftColumn";
            this.leftColumn.RowCount = 2;
            this.leftColumn.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.leftColumn.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.leftColumn.Size = new System.Drawing.Size(529, 1003);
            this.leftColumn.TabIndex = 4;
            // 
            // chartGyro
            // 
            this.chartGyro.BorderSkin.BackColor = System.Drawing.SystemColors.GrayText;
            this.chartGyro.BorderSkin.PageColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(37)))));
            chartArea1.AxisX.MaximumAutoSize = 0F;
            chartArea1.AxisX.Title = "time (ms)";
            chartArea1.AxisY.IsReversed = true;
            chartArea1.AxisY.Maximum = 3D;
            chartArea1.AxisY.MaximumAutoSize = 5F;
            chartArea1.AxisY.Minimum = -3D;
            chartArea1.AxisY.ScaleBreakStyle.StartFromZero = System.Windows.Forms.DataVisualization.Charting.StartFromZero.Yes;
            chartArea1.AxisY.Title = "deg/s";
            chartArea1.Name = "ChartArea1";
            this.chartGyro.ChartAreas.Add(chartArea1);
            this.chartGyro.Dock = System.Windows.Forms.DockStyle.Fill;
            legend1.Name = "Legend1";
            legend1.Position.Auto = false;
            legend1.Position.Height = 8.595041F;
            legend1.Position.Width = 20F;
            legend1.Position.X = 80F;
            this.chartGyro.Legends.Add(legend1);
            this.chartGyro.Location = new System.Drawing.Point(0, 352);
            this.chartGyro.Margin = new System.Windows.Forms.Padding(0);
            this.chartGyro.Name = "chartGyro";
            this.chartGyro.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.None;
            this.chartGyro.PaletteCustomColors = new System.Drawing.Color[] {
        System.Drawing.Color.Red,
        System.Drawing.Color.Blue,
        System.Drawing.Color.Green};
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series1.Legend = "Legend1";
            series1.Name = "Gx";
            series1.XAxisType = System.Windows.Forms.DataVisualization.Charting.AxisType.Secondary;
            series1.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Single;
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series2.Legend = "Legend1";
            series2.Name = "Gy";
            series2.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Single;
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series3.Legend = "Legend1";
            series3.Name = "Gz";
            series3.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Single;
            this.chartGyro.Series.Add(series1);
            this.chartGyro.Series.Add(series2);
            this.chartGyro.Series.Add(series3);
            this.chartGyro.Size = new System.Drawing.Size(529, 651);
            this.chartGyro.TabIndex = 11;
            this.chartGyro.Text = "BMI085";
            title1.Name = "BMI085 - Angles";
            title1.Text = "Gyroscope";
            this.chartGyro.Titles.Add(title1);
            // 
            // chartAccel
            // 
            this.chartAccel.BorderSkin.BackColor = System.Drawing.SystemColors.GrayText;
            this.chartAccel.BorderSkin.PageColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(37)))));
            chartArea2.AxisX.MaximumAutoSize = 0F;
            chartArea2.AxisX.Title = "time (ms)";
            chartArea2.AxisY.Maximum = 12D;
            chartArea2.AxisY.MaximumAutoSize = 5F;
            chartArea2.AxisY.Minimum = -12D;
            chartArea2.AxisY.ScaleBreakStyle.StartFromZero = System.Windows.Forms.DataVisualization.Charting.StartFromZero.Yes;
            chartArea2.AxisY.Title = "ms^2";
            chartArea2.Name = "ChartArea1";
            this.chartAccel.ChartAreas.Add(chartArea2);
            this.chartAccel.Dock = System.Windows.Forms.DockStyle.Fill;
            legend2.IsTextAutoFit = false;
            legend2.Name = "Legend1";
            legend2.Position.Auto = false;
            legend2.Position.Height = 8.595041F;
            legend2.Position.Width = 20F;
            legend2.Position.X = 80F;
            this.chartAccel.Legends.Add(legend2);
            this.chartAccel.Location = new System.Drawing.Point(0, 0);
            this.chartAccel.Margin = new System.Windows.Forms.Padding(0);
            this.chartAccel.Name = "chartAccel";
            this.chartAccel.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.None;
            this.chartAccel.PaletteCustomColors = new System.Drawing.Color[] {
        System.Drawing.Color.Red,
        System.Drawing.Color.Blue,
        System.Drawing.Color.Green};
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series4.Legend = "Legend1";
            series4.Name = "Ax";
            series4.XAxisType = System.Windows.Forms.DataVisualization.Charting.AxisType.Secondary;
            series4.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Single;
            series5.ChartArea = "ChartArea1";
            series5.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series5.Legend = "Legend1";
            series5.Name = "Ay";
            series5.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Single;
            series6.ChartArea = "ChartArea1";
            series6.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series6.Legend = "Legend1";
            series6.Name = "Az";
            series6.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Single;
            this.chartAccel.Series.Add(series4);
            this.chartAccel.Series.Add(series5);
            this.chartAccel.Series.Add(series6);
            this.chartAccel.Size = new System.Drawing.Size(529, 352);
            this.chartAccel.TabIndex = 2;
            this.chartAccel.Text = "BMI085";
            title2.Name = "BMI085 - Angles";
            title2.Text = "Accelerometer";
            this.chartAccel.Titles.Add(title2);
            // 
            // ListViewIMUData
            // 
            this.ListViewIMUData.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.ListViewIMUData.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ListViewIMUData.Font = new System.Drawing.Font("Cascadia Mono", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ListViewIMUData.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(35)))), ((int)(((byte)(35)))), ((int)(((byte)(35)))));
            this.ListViewIMUData.GridLines = true;
            this.ListViewIMUData.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.ListViewIMUData.HideSelection = false;
            this.ListViewIMUData.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem1,
            listViewItem2,
            listViewItem3,
            listViewItem4,
            listViewItem5,
            listViewItem6,
            listViewItem7,
            listViewItem8,
            listViewItem9});
            this.ListViewIMUData.Location = new System.Drawing.Point(1070, 0);
            this.ListViewIMUData.Margin = new System.Windows.Forms.Padding(0);
            this.ListViewIMUData.Name = "ListViewIMUData";
            this.ListViewIMUData.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.ListViewIMUData.Size = new System.Drawing.Size(180, 1009);
            this.ListViewIMUData.TabIndex = 6;
            this.ListViewIMUData.UseCompatibleStateImageBehavior = false;
            this.ListViewIMUData.View = System.Windows.Forms.View.List;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Controls.Add(this.chartAHRS, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.flowLayoutPanel1, 0, 1);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(538, 3);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 2;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 77.77778F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 22.22222F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(529, 1003);
            this.tableLayoutPanel2.TabIndex = 7;
            // 
            // chartAHRS
            // 
            chartArea3.AxisX.Title = "time (ms)";
            chartArea3.AxisY.Maximum = 90D;
            chartArea3.AxisY.MaximumAutoSize = 10F;
            chartArea3.AxisY.Minimum = -90D;
            chartArea3.AxisY.Title = "deg/s";
            chartArea3.Name = "ChartArea1";
            this.chartAHRS.ChartAreas.Add(chartArea3);
            this.chartAHRS.Dock = System.Windows.Forms.DockStyle.Fill;
            legend3.LegendStyle = System.Windows.Forms.DataVisualization.Charting.LegendStyle.Row;
            legend3.Name = "Legend1";
            legend3.Position.Auto = false;
            legend3.Position.Height = 3.409091F;
            legend3.Position.Width = 41.81185F;
            legend3.Position.X = 55.18815F;
            legend3.Position.Y = 5F;
            this.chartAHRS.Legends.Add(legend3);
            this.chartAHRS.Location = new System.Drawing.Point(0, 0);
            this.chartAHRS.Margin = new System.Windows.Forms.Padding(0);
            this.chartAHRS.Name = "chartAHRS";
            this.chartAHRS.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.None;
            this.chartAHRS.PaletteCustomColors = new System.Drawing.Color[] {
        System.Drawing.Color.Red,
        System.Drawing.Color.Blue,
        System.Drawing.Color.Green,
        System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192))))),
        System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255))))),
        System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))))};
            series7.ChartArea = "ChartArea1";
            series7.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series7.Legend = "Legend1";
            series7.LegendText = "X";
            series7.Name = "AngleX";
            series7.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Single;
            series8.ChartArea = "ChartArea1";
            series8.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series8.Legend = "Legend1";
            series8.LegendText = "Y";
            series8.Name = "AngleY";
            series8.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Single;
            series9.ChartArea = "ChartArea1";
            series9.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series9.Legend = "Legend1";
            series9.LegendText = "Z";
            series9.Name = "AngleZ";
            series9.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Single;
            series10.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            series10.BorderWidth = 2;
            series10.ChartArea = "ChartArea1";
            series10.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series10.Legend = "Legend1";
            series10.Name = "compX";
            series10.YValuesPerPoint = 4;
            series11.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            series11.BorderWidth = 2;
            series11.ChartArea = "ChartArea1";
            series11.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series11.Legend = "Legend1";
            series11.Name = "compY";
            series12.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            series12.BorderWidth = 2;
            series12.ChartArea = "ChartArea1";
            series12.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series12.Legend = "Legend1";
            series12.Name = "compZ";
            this.chartAHRS.Series.Add(series7);
            this.chartAHRS.Series.Add(series8);
            this.chartAHRS.Series.Add(series9);
            this.chartAHRS.Series.Add(series10);
            this.chartAHRS.Series.Add(series11);
            this.chartAHRS.Series.Add(series12);
            this.chartAHRS.Size = new System.Drawing.Size(529, 780);
            this.chartAHRS.TabIndex = 6;
            this.chartAHRS.Text = "chart1";
            title3.Name = "Title1";
            title3.Text = "AHRS algorithm";
            this.chartAHRS.Titles.Add(title3);
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.flowLayoutPanel1.Controls.Add(this.circleAnglePicker1);
            this.flowLayoutPanel1.Controls.Add(this.circleAnglePicker2);
            this.flowLayoutPanel1.Controls.Add(this.circleAnglePicker3);
            this.flowLayoutPanel1.Location = new System.Drawing.Point(3, 783);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(523, 217);
            this.flowLayoutPanel1.TabIndex = 7;
            // 
            // circleAnglePicker1
            // 
            this.circleAnglePicker1.AutoScrollMargin = new System.Drawing.Size(0, 0);
            this.circleAnglePicker1.AutoScrollMinSize = new System.Drawing.Size(0, 0);
            this.circleAnglePicker1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.circleAnglePicker1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.circleAnglePicker1.CircleBackColor = System.Drawing.Color.White;
            this.circleAnglePicker1.CoreType = System.Windows.Forms.CoreType.Ellipse;
            this.circleAnglePicker1.CoreWidth = 5;
            this.circleAnglePicker1.InnerCircle = true;
            this.circleAnglePicker1.InnerCircleColor = System.Drawing.Color.FromArgb(((int)(((byte)(150)))), ((int)(((byte)(150)))), ((int)(((byte)(150)))));
            this.circleAnglePicker1.InnerCircleOffset = 4;
            this.circleAnglePicker1.Location = new System.Drawing.Point(10, 10);
            this.circleAnglePicker1.Margin = new System.Windows.Forms.Padding(10);
            this.circleAnglePicker1.Name = "circleAnglePicker1";
            this.circleAnglePicker1.Size = new System.Drawing.Size(128, 128);
            this.circleAnglePicker1.TabIndex = 0;
            // 
            // circleAnglePicker2
            // 
            this.circleAnglePicker2.AutoScrollMargin = new System.Drawing.Size(0, 0);
            this.circleAnglePicker2.AutoScrollMinSize = new System.Drawing.Size(0, 0);
            this.circleAnglePicker2.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.circleAnglePicker2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.circleAnglePicker2.CircleBackColor = System.Drawing.Color.White;
            this.circleAnglePicker2.CoreType = System.Windows.Forms.CoreType.Ellipse;
            this.circleAnglePicker2.CoreWidth = 5;
            this.circleAnglePicker2.InnerCircle = true;
            this.circleAnglePicker2.InnerCircleColor = System.Drawing.Color.FromArgb(((int)(((byte)(150)))), ((int)(((byte)(150)))), ((int)(((byte)(150)))));
            this.circleAnglePicker2.InnerCircleOffset = 4;
            this.circleAnglePicker2.Location = new System.Drawing.Point(158, 10);
            this.circleAnglePicker2.Margin = new System.Windows.Forms.Padding(10);
            this.circleAnglePicker2.Name = "circleAnglePicker2";
            this.circleAnglePicker2.Size = new System.Drawing.Size(128, 128);
            this.circleAnglePicker2.TabIndex = 1;
            // 
            // circleAnglePicker3
            // 
            this.circleAnglePicker3.AutoScrollMargin = new System.Drawing.Size(0, 0);
            this.circleAnglePicker3.AutoScrollMinSize = new System.Drawing.Size(0, 0);
            this.circleAnglePicker3.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.circleAnglePicker3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.circleAnglePicker3.CircleBackColor = System.Drawing.Color.White;
            this.circleAnglePicker3.CoreType = System.Windows.Forms.CoreType.Ellipse;
            this.circleAnglePicker3.CoreWidth = 5;
            this.circleAnglePicker3.InnerCircle = true;
            this.circleAnglePicker3.InnerCircleColor = System.Drawing.Color.FromArgb(((int)(((byte)(150)))), ((int)(((byte)(150)))), ((int)(((byte)(150)))));
            this.circleAnglePicker3.InnerCircleOffset = 4;
            this.circleAnglePicker3.Location = new System.Drawing.Point(306, 10);
            this.circleAnglePicker3.Margin = new System.Windows.Forms.Padding(10);
            this.circleAnglePicker3.Name = "circleAnglePicker3";
            this.circleAnglePicker3.Size = new System.Drawing.Size(128, 128);
            this.circleAnglePicker3.TabIndex = 2;
            // 
            // CIMUDEBUG
            // 
            this.CIMUDEBUG.Controls.Add(this.customerIMUMainLayout);
            this.CIMUDEBUG.Location = new System.Drawing.Point(4, 22);
            this.CIMUDEBUG.Name = "CIMUDEBUG";
            this.CIMUDEBUG.Padding = new System.Windows.Forms.Padding(3);
            this.CIMUDEBUG.Size = new System.Drawing.Size(1256, 655);
            this.CIMUDEBUG.TabIndex = 1;
            this.CIMUDEBUG.Text = "Customer IMU Debug";
            this.CIMUDEBUG.UseVisualStyleBackColor = true;
            // 
            // customerIMUMainLayout
            // 
            this.customerIMUMainLayout.ColumnCount = 2;
            this.customerIMUMainLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.customerIMUMainLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.customerIMUMainLayout.Controls.Add(this.customerIMUGraphView, 0, 0);
            this.customerIMUMainLayout.Controls.Add(this.flowLayoutPanel2, 1, 0);
            this.customerIMUMainLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.customerIMUMainLayout.Location = new System.Drawing.Point(3, 3);
            this.customerIMUMainLayout.Name = "customerIMUMainLayout";
            this.customerIMUMainLayout.RowCount = 1;
            this.customerIMUMainLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.customerIMUMainLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.customerIMUMainLayout.Size = new System.Drawing.Size(1250, 649);
            this.customerIMUMainLayout.TabIndex = 0;
            // 
            // customerIMUGraphView
            // 
            this.customerIMUGraphView.ColumnCount = 1;
            this.customerIMUGraphView.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.customerIMUGraphView.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.customerIMUGraphView.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.customerIMUGraphView.Controls.Add(this.StatisticCustomerImu, 0, 0);
            this.customerIMUGraphView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.customerIMUGraphView.Location = new System.Drawing.Point(3, 3);
            this.customerIMUGraphView.Name = "customerIMUGraphView";
            this.customerIMUGraphView.RowCount = 2;
            this.customerIMUGraphView.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 90F));
            this.customerIMUGraphView.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.customerIMUGraphView.Size = new System.Drawing.Size(619, 643);
            this.customerIMUGraphView.TabIndex = 0;
            // 
            // StatisticCustomerImu
            // 
            chartArea4.AxisX.LabelStyle.Enabled = false;
            chartArea4.AxisX.MajorGrid.Enabled = false;
            chartArea4.AxisX.MajorTickMark.Enabled = false;
            chartArea4.AxisX.MinorTickMark.Enabled = true;
            chartArea4.AxisX.MinorTickMark.Interval = 3D;
            chartArea4.AxisY.Maximum = 10D;
            chartArea4.AxisY.Minimum = -10D;
            chartArea4.Name = "ChartArea1";
            this.StatisticCustomerImu.ChartAreas.Add(chartArea4);
            this.StatisticCustomerImu.Dock = System.Windows.Forms.DockStyle.Fill;
            this.StatisticCustomerImu.Location = new System.Drawing.Point(3, 3);
            this.StatisticCustomerImu.Name = "StatisticCustomerImu";
            this.StatisticCustomerImu.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.Pastel;
            series13.BorderWidth = 2;
            series13.ChartArea = "ChartArea1";
            series13.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.ErrorBar;
            series13.Name = "Statistic";
            series13.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.Pastel;
            series13.YValuesPerPoint = 4;
            series14.BorderWidth = 2;
            series14.ChartArea = "ChartArea1";
            series14.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.ErrorBar;
            series14.Color = System.Drawing.Color.Red;
            series14.Name = "avg";
            series14.YValuesPerPoint = 4;
            this.StatisticCustomerImu.Series.Add(series13);
            this.StatisticCustomerImu.Series.Add(series14);
            this.StatisticCustomerImu.Size = new System.Drawing.Size(613, 572);
            this.StatisticCustomerImu.TabIndex = 1;
            this.StatisticCustomerImu.Text = "x Axis";
            title4.Name = "X";
            this.StatisticCustomerImu.Titles.Add(title4);
            // 
            // flowLayoutPanel2
            // 
            this.flowLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel2.Location = new System.Drawing.Point(628, 3);
            this.flowLayoutPanel2.Name = "flowLayoutPanel2";
            this.flowLayoutPanel2.Size = new System.Drawing.Size(619, 643);
            this.flowLayoutPanel2.TabIndex = 1;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.ProximitySwitchMainLayout);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(1256, 655);
            this.tabPage1.TabIndex = 2;
            this.tabPage1.Text = "Proximity Switch";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // ProximitySwitchMainLayout
            // 
            this.ProximitySwitchMainLayout.ColumnCount = 2;
            this.ProximitySwitchMainLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.ProximitySwitchMainLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 85F));
            this.ProximitySwitchMainLayout.Controls.Add(this.ProximityValue, 1, 0);
            this.ProximitySwitchMainLayout.Controls.Add(this.ProximitySwitch, 0, 0);
            this.ProximitySwitchMainLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ProximitySwitchMainLayout.Location = new System.Drawing.Point(3, 3);
            this.ProximitySwitchMainLayout.Name = "ProximitySwitchMainLayout";
            this.ProximitySwitchMainLayout.RowCount = 2;
            this.ProximitySwitchMainLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.ProximitySwitchMainLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.ProximitySwitchMainLayout.Size = new System.Drawing.Size(1250, 649);
            this.ProximitySwitchMainLayout.TabIndex = 0;
            // 
            // ProximityValue
            // 
            this.ProximityValue.AutoSize = true;
            this.ProximityValue.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ProximityValue.Location = new System.Drawing.Point(190, 0);
            this.ProximityValue.Name = "ProximityValue";
            this.ProximityValue.Size = new System.Drawing.Size(1057, 25);
            this.ProximityValue.TabIndex = 1;
            this.ProximityValue.Text = "0";
            // 
            // ProximitySwitch
            // 
            this.ProximitySwitch.AutoSize = true;
            this.ProximitySwitch.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ProximitySwitch.Location = new System.Drawing.Point(3, 0);
            this.ProximitySwitch.Name = "ProximitySwitch";
            this.ProximitySwitch.Size = new System.Drawing.Size(181, 25);
            this.ProximitySwitch.TabIndex = 0;
            this.ProximitySwitch.Text = "Proximity:";
            // 
            // AltimerData
            // 
            this.AltimerData.Controls.Add(this.AltimeterLayout);
            this.AltimerData.Location = new System.Drawing.Point(4, 22);
            this.AltimerData.Name = "AltimerData";
            this.AltimerData.Padding = new System.Windows.Forms.Padding(3);
            this.AltimerData.Size = new System.Drawing.Size(1256, 655);
            this.AltimerData.TabIndex = 3;
            this.AltimerData.Text = "Altimeter";
            this.AltimerData.UseVisualStyleBackColor = true;
            // 
            // AltimeterLayout
            // 
            this.AltimeterLayout.ColumnCount = 2;
            this.AltimeterLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.AltimeterLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 85F));
            this.AltimeterLayout.Controls.Add(this.AltimeterValue, 1, 0);
            this.AltimeterLayout.Controls.Add(this.AltimeterPrefix, 0, 0);
            this.AltimeterLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AltimeterLayout.Location = new System.Drawing.Point(3, 3);
            this.AltimeterLayout.Name = "AltimeterLayout";
            this.AltimeterLayout.RowCount = 5;
            this.AltimeterLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.AltimeterLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.AltimeterLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.AltimeterLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.AltimeterLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 10F));
            this.AltimeterLayout.Size = new System.Drawing.Size(1250, 649);
            this.AltimeterLayout.TabIndex = 1;
            // 
            // AltimeterValue
            // 
            this.AltimeterValue.AutoSize = true;
            this.AltimeterValue.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AltimeterValue.Location = new System.Drawing.Point(187, 0);
            this.AltimeterValue.Margin = new System.Windows.Forms.Padding(0);
            this.AltimeterValue.Name = "AltimeterValue";
            this.AltimeterValue.Size = new System.Drawing.Size(1063, 30);
            this.AltimeterValue.TabIndex = 1;
            this.AltimeterValue.Text = "0";
            // 
            // AltimeterPrefix
            // 
            this.AltimeterPrefix.AutoSize = true;
            this.AltimeterPrefix.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AltimeterPrefix.Location = new System.Drawing.Point(0, 0);
            this.AltimeterPrefix.Margin = new System.Windows.Forms.Padding(0);
            this.AltimeterPrefix.Name = "AltimeterPrefix";
            this.AltimeterPrefix.Size = new System.Drawing.Size(187, 30);
            this.AltimeterPrefix.TabIndex = 0;
            this.AltimeterPrefix.Text = "Altimeter:";
            // 
            // FFTTabPage
            // 
            this.FFTTabPage.Controls.Add(this.fftChart);
            this.FFTTabPage.Location = new System.Drawing.Point(4, 22);
            this.FFTTabPage.Margin = new System.Windows.Forms.Padding(0);
            this.FFTTabPage.Name = "FFTTabPage";
            this.FFTTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.FFTTabPage.Size = new System.Drawing.Size(1256, 655);
            this.FFTTabPage.TabIndex = 4;
            this.FFTTabPage.Text = "Spectrum Analysis";
            this.FFTTabPage.UseVisualStyleBackColor = true;
            // 
            // fftChart
            // 
            chartArea5.AxisX.Minimum = 0D;
            chartArea5.AxisX.Title = "Frequency (Hz)";
            chartArea5.AxisY.Title = "Amplitude (g)";
            chartArea5.Name = "ChartArea1";
            this.fftChart.ChartAreas.Add(chartArea5);
            this.fftChart.Dock = System.Windows.Forms.DockStyle.Fill;
            legend4.Name = "Legend1";
            this.fftChart.Legends.Add(legend4);
            this.fftChart.Location = new System.Drawing.Point(3, 3);
            this.fftChart.Name = "fftChart";
            this.fftChart.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.None;
            this.fftChart.PaletteCustomColors = new System.Drawing.Color[] {
        System.Drawing.Color.Blue,
        System.Drawing.Color.Red,
        System.Drawing.Color.Lime,
        System.Drawing.Color.Aqua};
            series15.ChartArea = "ChartArea1";
            series15.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series15.Legend = "Legend1";
            series15.Name = "X";
            series16.ChartArea = "ChartArea1";
            series16.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series16.Legend = "Legend1";
            series16.Name = "Y";
            series17.ChartArea = "ChartArea1";
            series17.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series17.Legend = "Legend1";
            series17.Name = "Z";
            this.fftChart.Series.Add(series15);
            this.fftChart.Series.Add(series16);
            this.fftChart.Series.Add(series17);
            this.fftChart.Size = new System.Drawing.Size(1250, 649);
            this.fftChart.TabIndex = 0;
            this.fftChart.Text = "FFTChart";
            // 
            // GNSSTab
            // 
            this.GNSSTab.Controls.Add(this.GNSSLayout);
            this.GNSSTab.Location = new System.Drawing.Point(4, 22);
            this.GNSSTab.Name = "GNSSTab";
            this.GNSSTab.Size = new System.Drawing.Size(1256, 655);
            this.GNSSTab.TabIndex = 5;
            this.GNSSTab.Text = "GNSS";
            this.GNSSTab.UseVisualStyleBackColor = true;
            // 
            // GNSSLayout
            // 
            this.GNSSLayout.ColumnCount = 1;
            this.GNSSLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.GNSSLayout.Controls.Add(this.GNSSMapControl, 0, 0);
            this.GNSSLayout.Controls.Add(this.GNSSEpoch, 0, 1);
            this.GNSSLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GNSSLayout.Location = new System.Drawing.Point(0, 0);
            this.GNSSLayout.Name = "GNSSLayout";
            this.GNSSLayout.RowCount = 2;
            this.GNSSLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.GNSSLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.GNSSLayout.Size = new System.Drawing.Size(1256, 655);
            this.GNSSLayout.TabIndex = 0;
            // 
            // GNSSMapControl
            // 
            this.GNSSMapControl.Bearing = 0F;
            this.GNSSMapControl.CanDragMap = true;
            this.GNSSMapControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GNSSMapControl.EmptyTileColor = System.Drawing.Color.Navy;
            this.GNSSMapControl.GrayScaleMode = false;
            this.GNSSMapControl.HelperLineOption = GMap.NET.WindowsForms.HelperLineOptions.DontShow;
            this.GNSSMapControl.LevelsKeepInMemmory = 5;
            this.GNSSMapControl.Location = new System.Drawing.Point(3, 3);
            this.GNSSMapControl.MarkersEnabled = true;
            this.GNSSMapControl.MaxZoom = 2;
            this.GNSSMapControl.MinZoom = 2;
            this.GNSSMapControl.MouseWheelZoomEnabled = true;
            this.GNSSMapControl.MouseWheelZoomType = GMap.NET.MouseWheelZoomType.MousePositionAndCenter;
            this.GNSSMapControl.Name = "GNSSMapControl";
            this.GNSSMapControl.NegativeMode = false;
            this.GNSSMapControl.PolygonsEnabled = true;
            this.GNSSMapControl.RetryLoadTile = 0;
            this.GNSSMapControl.RoutesEnabled = true;
            this.GNSSMapControl.ScaleMode = GMap.NET.WindowsForms.ScaleModes.Integer;
            this.GNSSMapControl.SelectedAreaFillColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(65)))), ((int)(((byte)(105)))), ((int)(((byte)(225)))));
            this.GNSSMapControl.ShowTileGridLines = false;
            this.GNSSMapControl.Size = new System.Drawing.Size(1250, 624);
            this.GNSSMapControl.TabIndex = 1;
            this.GNSSMapControl.Zoom = 0D;
            // 
            // GNSSEpoch
            // 
            this.GNSSEpoch.AutoSize = true;
            this.GNSSEpoch.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GNSSEpoch.Location = new System.Drawing.Point(3, 630);
            this.GNSSEpoch.Name = "GNSSEpoch";
            this.GNSSEpoch.Size = new System.Drawing.Size(1250, 25);
            this.GNSSEpoch.TabIndex = 2;
            this.GNSSEpoch.Text = "Packet counter:";
            // 
            // MainView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 681);
            this.Controls.Add(this.AltimerTab);
            this.Name = "MainView";
            this.Text = "Hardware Debugging Tool";
            this.AltimerTab.ResumeLayout(false);
            this.DebugIMU.ResumeLayout(false);
            this.MainLayout.ResumeLayout(false);
            this.leftColumn.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chartGyro)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chartAccel)).EndInit();
            this.tableLayoutPanel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chartAHRS)).EndInit();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.CIMUDEBUG.ResumeLayout(false);
            this.customerIMUMainLayout.ResumeLayout(false);
            this.customerIMUGraphView.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.StatisticCustomerImu)).EndInit();
            this.tabPage1.ResumeLayout(false);
            this.ProximitySwitchMainLayout.ResumeLayout(false);
            this.ProximitySwitchMainLayout.PerformLayout();
            this.AltimerData.ResumeLayout(false);
            this.AltimeterLayout.ResumeLayout(false);
            this.AltimeterLayout.PerformLayout();
            this.FFTTabPage.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.fftChart)).EndInit();
            this.GNSSTab.ResumeLayout(false);
            this.GNSSLayout.ResumeLayout(false);
            this.GNSSLayout.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl AltimerTab;
        private System.Windows.Forms.TabPage DebugIMU;
        private System.Windows.Forms.TableLayoutPanel MainLayout;
        private System.Windows.Forms.TableLayoutPanel leftColumn;
        private System.Windows.Forms.DataVisualization.Charting.Chart chartGyro;
        private System.Windows.Forms.DataVisualization.Charting.Chart chartAccel;
        private System.Windows.Forms.ListView ListViewIMUData;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.DataVisualization.Charting.Chart chartAHRS;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.CircleAnglePicker circleAnglePicker1;
        private System.Windows.Forms.CircleAnglePicker circleAnglePicker2;
        private System.Windows.Forms.CircleAnglePicker circleAnglePicker3;
        private System.Windows.Forms.TabPage CIMUDEBUG;
        private System.Windows.Forms.TableLayoutPanel customerIMUMainLayout;
        private System.Windows.Forms.TableLayoutPanel customerIMUGraphView;
        private System.Windows.Forms.DataVisualization.Charting.Chart StatisticCustomerImu;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TableLayoutPanel ProximitySwitchMainLayout;
        private System.Windows.Forms.Label ProximitySwitch;
        private System.Windows.Forms.Label ProximityValue;
        private System.Windows.Forms.TabPage AltimerData;
        private System.Windows.Forms.TableLayoutPanel AltimeterLayout;
        private System.Windows.Forms.Label AltimeterValue;
        private System.Windows.Forms.Label AltimeterPrefix;
        private System.Windows.Forms.TabPage FFTTabPage;
        private System.Windows.Forms.DataVisualization.Charting.Chart fftChart;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2;
        private System.Windows.Forms.TabPage GNSSTab;
        private System.Windows.Forms.TableLayoutPanel GNSSLayout;
        private GMap.NET.WindowsForms.GMapControl GNSSMapControl;
        private System.Windows.Forms.Label GNSSEpoch;
    }
}

