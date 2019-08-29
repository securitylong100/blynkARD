namespace Csharp_8266
{
    partial class Wifi_Form
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
            this.components = new System.ComponentModel.Container();
            this.dgvData = new System.Windows.Forms.DataGridView();
            this.btnStart = new System.Windows.Forms.Button();
            this.lbTimer = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.cmbModel = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.cmbMTo = new System.Windows.Forms.ComboBox();
            this.cmbHTo = new System.Windows.Forms.ComboBox();
            this.dtTo = new System.Windows.Forms.DateTimePicker();
            this.cmbMFrom = new System.Windows.Forms.ComboBox();
            this.cmbHFrom = new System.Windows.Forms.ComboBox();
            this.dtFrom = new System.Windows.Forms.DateTimePicker();
            this.lbProcessing = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dgvData)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // dgvData
            // 
            this.dgvData.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dgvData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvData.Location = new System.Drawing.Point(0, 130);
            this.dgvData.Name = "dgvData";
            this.dgvData.Size = new System.Drawing.Size(528, 174);
            this.dgvData.TabIndex = 0;
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(271, 101);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 23);
            this.btnStart.TabIndex = 1;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.button1_Click);
            // 
            // lbTimer
            // 
            this.lbTimer.AutoSize = true;
            this.lbTimer.Location = new System.Drawing.Point(495, 111);
            this.lbTimer.Name = "lbTimer";
            this.lbTimer.Size = new System.Drawing.Size(21, 13);
            this.lbTimer.TabIndex = 2;
            this.lbTimer.Text = "0 s";
            // 
            // timer1
            // 
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // cmbModel
            // 
            this.cmbModel.FormattingEnabled = true;
            this.cmbModel.Location = new System.Drawing.Point(12, 25);
            this.cmbModel.Name = "cmbModel";
            this.cmbModel.Size = new System.Drawing.Size(121, 21);
            this.cmbModel.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Model";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cmbMTo);
            this.groupBox1.Controls.Add(this.cmbHTo);
            this.groupBox1.Controls.Add(this.dtTo);
            this.groupBox1.Controls.Add(this.cmbMFrom);
            this.groupBox1.Controls.Add(this.cmbHFrom);
            this.groupBox1.Controls.Add(this.dtFrom);
            this.groupBox1.Location = new System.Drawing.Point(12, 52);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(205, 72);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Thời gian";
            // 
            // cmbMTo
            // 
            this.cmbMTo.DropDownWidth = 60;
            this.cmbMTo.FormatString = "MM";
            this.cmbMTo.FormattingEnabled = true;
            this.cmbMTo.Items.AddRange(new object[] {
            "00",
            "01",
            "02",
            "03",
            "04",
            "05",
            "06",
            "07",
            "08",
            "09",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16",
            "17",
            "18",
            "19",
            "20",
            "21",
            "22",
            "23",
            "24",
            "25",
            "26",
            "27",
            "28",
            "29",
            "30",
            "31",
            "32",
            "33",
            "34",
            "35",
            "36",
            "37",
            "38",
            "39",
            "40",
            "41",
            "42",
            "43",
            "44",
            "45",
            "46",
            "47",
            "48",
            "49",
            "50",
            "51",
            "52",
            "53",
            "54",
            "55",
            "56",
            "57",
            "58",
            "59"});
            this.cmbMTo.Location = new System.Drawing.Point(155, 44);
            this.cmbMTo.Name = "cmbMTo";
            this.cmbMTo.Size = new System.Drawing.Size(41, 21);
            this.cmbMTo.TabIndex = 11;
            // 
            // cmbHTo
            // 
            this.cmbHTo.DropDownWidth = 24;
            this.cmbHTo.FormatString = "HH";
            this.cmbHTo.FormattingEnabled = true;
            this.cmbHTo.Items.AddRange(new object[] {
            "00",
            "01",
            "02",
            "03",
            "04",
            "05",
            "06",
            "07",
            "08",
            "09",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16",
            "17",
            "18",
            "19",
            "20",
            "21",
            "22",
            "23"});
            this.cmbHTo.Location = new System.Drawing.Point(108, 44);
            this.cmbHTo.Name = "cmbHTo";
            this.cmbHTo.Size = new System.Drawing.Size(41, 21);
            this.cmbHTo.TabIndex = 10;
            // 
            // dtTo
            // 
            this.dtTo.CustomFormat = "dd/mm/yyyy";
            this.dtTo.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtTo.Location = new System.Drawing.Point(6, 44);
            this.dtTo.Name = "dtTo";
            this.dtTo.Size = new System.Drawing.Size(96, 20);
            this.dtTo.TabIndex = 9;
            // 
            // cmbMFrom
            // 
            this.cmbMFrom.DropDownWidth = 60;
            this.cmbMFrom.FormatString = "MM";
            this.cmbMFrom.FormattingEnabled = true;
            this.cmbMFrom.Items.AddRange(new object[] {
            "00",
            "01",
            "02",
            "03",
            "04",
            "05",
            "06",
            "07",
            "08",
            "09",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16",
            "17",
            "18",
            "19",
            "20",
            "21",
            "22",
            "23",
            "24",
            "25",
            "26",
            "27",
            "28",
            "29",
            "30",
            "31",
            "32",
            "33",
            "34",
            "35",
            "36",
            "37",
            "38",
            "39",
            "40",
            "41",
            "42",
            "43",
            "44",
            "45",
            "46",
            "47",
            "48",
            "49",
            "50",
            "51",
            "52",
            "53",
            "54",
            "55",
            "56",
            "57",
            "58",
            "59"});
            this.cmbMFrom.Location = new System.Drawing.Point(155, 19);
            this.cmbMFrom.Name = "cmbMFrom";
            this.cmbMFrom.Size = new System.Drawing.Size(41, 21);
            this.cmbMFrom.TabIndex = 8;
            // 
            // cmbHFrom
            // 
            this.cmbHFrom.DropDownWidth = 24;
            this.cmbHFrom.FormatString = "HH";
            this.cmbHFrom.FormattingEnabled = true;
            this.cmbHFrom.Items.AddRange(new object[] {
            "00",
            "01",
            "02",
            "03",
            "04",
            "05",
            "06",
            "07",
            "08",
            "09",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16",
            "17",
            "18",
            "19",
            "20",
            "21",
            "22",
            "23"});
            this.cmbHFrom.Location = new System.Drawing.Point(108, 19);
            this.cmbHFrom.Name = "cmbHFrom";
            this.cmbHFrom.Size = new System.Drawing.Size(41, 21);
            this.cmbHFrom.TabIndex = 7;
            // 
            // dtFrom
            // 
            this.dtFrom.CustomFormat = "dd/mm/yyyy";
            this.dtFrom.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtFrom.Location = new System.Drawing.Point(6, 19);
            this.dtFrom.Name = "dtFrom";
            this.dtFrom.Size = new System.Drawing.Size(96, 20);
            this.dtFrom.TabIndex = 6;
            // 
            // lbProcessing
            // 
            this.lbProcessing.AutoSize = true;
            this.lbProcessing.Location = new System.Drawing.Point(433, 111);
            this.lbProcessing.Name = "lbProcessing";
            this.lbProcessing.Size = new System.Drawing.Size(35, 13);
            this.lbProcessing.TabIndex = 7;
            this.lbProcessing.Text = "label2";
            this.lbProcessing.Visible = false;
            // 
            // Wifi_Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(528, 304);
            this.Controls.Add(this.lbProcessing);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cmbModel);
            this.Controls.Add(this.lbTimer);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.dgvData);
            this.Name = "Wifi_Form";
            this.Text = "Wifi_Form";
            this.Load += new System.EventHandler(this.Wifi_Form_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvData)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvData;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Label lbTimer;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ComboBox cmbModel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.DateTimePicker dtFrom;
        private System.Windows.Forms.ComboBox cmbHFrom;
        private System.Windows.Forms.ComboBox cmbMFrom;
        private System.Windows.Forms.ComboBox cmbMTo;
        private System.Windows.Forms.ComboBox cmbHTo;
        private System.Windows.Forms.DateTimePicker dtTo;
        private System.Windows.Forms.Label lbProcessing;
    }
}