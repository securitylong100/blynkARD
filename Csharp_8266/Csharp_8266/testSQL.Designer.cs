namespace Csharp_8266
{
    partial class testSQL
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.trInspect = new System.Windows.Forms.TreeView();
            this.btnSearch = new System.Windows.Forms.Button();
            this.dgvdt = new System.Windows.Forms.DataGridView();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.tsProcessing = new System.Windows.Forms.ToolStripStatusLabel();
            this.tsTime = new System.Windows.Forms.ToolStripStatusLabel();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtBarcode = new System.Windows.Forms.TextBox();
            this.cmbModel = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.dtDatef = new System.Windows.Forms.DateTimePicker();
            this.cmbMinf = new System.Windows.Forms.ComboBox();
            this.cmbHoursf = new System.Windows.Forms.ComboBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.dtDatet = new System.Windows.Forms.DateTimePicker();
            this.cmbMint = new System.Windows.Forms.ComboBox();
            this.cmbHourst = new System.Windows.Forms.ComboBox();
            this.btnCSV = new System.Windows.Forms.Button();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvdt)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.trInspect);
            this.groupBox1.Location = new System.Drawing.Point(448, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(155, 192);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Inspect";
            // 
            // trInspect
            // 
            this.trInspect.CheckBoxes = true;
            this.trInspect.Dock = System.Windows.Forms.DockStyle.Fill;
            this.trInspect.Location = new System.Drawing.Point(3, 16);
            this.trInspect.Name = "trInspect";
            this.trInspect.Size = new System.Drawing.Size(149, 173);
            this.trInspect.TabIndex = 8;
            this.trInspect.AfterCheck += new System.Windows.Forms.TreeViewEventHandler(this.trInspect_AfterCheck);
            // 
            // btnSearch
            // 
            this.btnSearch.Location = new System.Drawing.Point(141, 126);
            this.btnSearch.Name = "btnSearch";
            this.btnSearch.Size = new System.Drawing.Size(92, 60);
            this.btnSearch.TabIndex = 9;
            this.btnSearch.Text = "Tìm";
            this.btnSearch.UseVisualStyleBackColor = true;
            this.btnSearch.Click += new System.EventHandler(this.btnSearch_Click);
            // 
            // dgvdt
            // 
            this.dgvdt.AllowUserToOrderColumns = true;
            this.dgvdt.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dgvdt.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvdt.Location = new System.Drawing.Point(0, 192);
            this.dgvdt.Name = "dgvdt";
            this.dgvdt.Size = new System.Drawing.Size(605, 186);
            this.dgvdt.TabIndex = 10;
            this.dgvdt.VirtualMode = true;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsProcessing,
            this.tsTime});
            this.statusStrip1.Location = new System.Drawing.Point(0, 381);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(605, 22);
            this.statusStrip1.TabIndex = 13;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // tsProcessing
            // 
            this.tsProcessing.Name = "tsProcessing";
            this.tsProcessing.Size = new System.Drawing.Size(34, 17);
            this.tsProcessing.Text = "none";
            // 
            // tsTime
            // 
            this.tsTime.Name = "tsTime";
            this.tsTime.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tsTime.Size = new System.Drawing.Size(21, 17);
            this.tsTime.Text = "0 s";
            // 
            // timer1
            // 
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.txtBarcode);
            this.panel1.Controls.Add(this.cmbModel);
            this.panel1.Location = new System.Drawing.Point(245, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(200, 192);
            this.panel1.TabIndex = 14;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 59);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Barcode";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "Model";
            // 
            // txtBarcode
            // 
            this.txtBarcode.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtBarcode.Location = new System.Drawing.Point(3, 75);
            this.txtBarcode.Multiline = true;
            this.txtBarcode.Name = "txtBarcode";
            this.txtBarcode.Size = new System.Drawing.Size(194, 111);
            this.txtBarcode.TabIndex = 7;
            // 
            // cmbModel
            // 
            this.cmbModel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cmbModel.FormattingEnabled = true;
            this.cmbModel.Location = new System.Drawing.Point(45, 23);
            this.cmbModel.Name = "cmbModel";
            this.cmbModel.Size = new System.Drawing.Size(131, 21);
            this.cmbModel.TabIndex = 6;
            this.cmbModel.TextChanged += new System.EventHandler(this.cmbModel_TextChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.dtDatef);
            this.groupBox2.Controls.Add(this.cmbMinf);
            this.groupBox2.Controls.Add(this.cmbHoursf);
            this.groupBox2.Location = new System.Drawing.Point(3, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(239, 51);
            this.groupBox2.TabIndex = 17;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Từ ngày";
            // 
            // dtDatef
            // 
            this.dtDatef.CustomFormat = "yyyy-MM-dd";
            this.dtDatef.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtDatef.Location = new System.Drawing.Point(6, 21);
            this.dtDatef.Name = "dtDatef";
            this.dtDatef.Size = new System.Drawing.Size(106, 20);
            this.dtDatef.TabIndex = 0;
            // 
            // cmbMinf
            // 
            this.cmbMinf.FormattingEnabled = true;
            this.cmbMinf.Items.AddRange(new object[] {
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
            this.cmbMinf.Location = new System.Drawing.Point(177, 20);
            this.cmbMinf.Name = "cmbMinf";
            this.cmbMinf.Size = new System.Drawing.Size(53, 21);
            this.cmbMinf.TabIndex = 18;
            this.cmbMinf.Text = "00";
            // 
            // cmbHoursf
            // 
            this.cmbHoursf.FormattingEnabled = true;
            this.cmbHoursf.Items.AddRange(new object[] {
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
            this.cmbHoursf.Location = new System.Drawing.Point(118, 20);
            this.cmbHoursf.Name = "cmbHoursf";
            this.cmbHoursf.Size = new System.Drawing.Size(53, 21);
            this.cmbHoursf.TabIndex = 17;
            this.cmbHoursf.Text = "00";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.dtDatet);
            this.groupBox3.Controls.Add(this.cmbMint);
            this.groupBox3.Controls.Add(this.cmbHourst);
            this.groupBox3.Location = new System.Drawing.Point(3, 69);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(239, 51);
            this.groupBox3.TabIndex = 18;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Đến ngày";
            // 
            // dtDatet
            // 
            this.dtDatet.CustomFormat = "yyyy-MM-dd";
            this.dtDatet.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtDatet.Location = new System.Drawing.Point(6, 19);
            this.dtDatet.Name = "dtDatet";
            this.dtDatet.Size = new System.Drawing.Size(106, 20);
            this.dtDatet.TabIndex = 19;
            // 
            // cmbMint
            // 
            this.cmbMint.FormattingEnabled = true;
            this.cmbMint.Items.AddRange(new object[] {
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
            this.cmbMint.Location = new System.Drawing.Point(177, 18);
            this.cmbMint.Name = "cmbMint";
            this.cmbMint.Size = new System.Drawing.Size(53, 21);
            this.cmbMint.TabIndex = 18;
            this.cmbMint.Text = "59";
            // 
            // cmbHourst
            // 
            this.cmbHourst.FormattingEnabled = true;
            this.cmbHourst.Items.AddRange(new object[] {
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
            this.cmbHourst.Location = new System.Drawing.Point(118, 18);
            this.cmbHourst.Name = "cmbHourst";
            this.cmbHourst.Size = new System.Drawing.Size(53, 21);
            this.cmbHourst.TabIndex = 17;
            this.cmbHourst.Text = "23";
            // 
            // btnCSV
            // 
            this.btnCSV.Location = new System.Drawing.Point(9, 126);
            this.btnCSV.Name = "btnCSV";
            this.btnCSV.Size = new System.Drawing.Size(92, 60);
            this.btnCSV.TabIndex = 19;
            this.btnCSV.Text = "CSV";
            this.btnCSV.UseVisualStyleBackColor = true;
            this.btnCSV.Click += new System.EventHandler(this.btnCSV_Click);
            // 
            // timer2
            // 
            this.timer2.Interval = 10;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // testSQL
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(605, 403);
            this.Controls.Add(this.btnCSV);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.btnSearch);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.dgvdt);
            this.Name = "testSQL";
            this.Text = "testSQL";
            this.groupBox1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgvdt)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TreeView trInspect;
        private System.Windows.Forms.Button btnSearch;
        private System.Windows.Forms.DataGridView dgvdt;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel tsProcessing;
        private System.Windows.Forms.ToolStripStatusLabel tsTime;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtBarcode;
        private System.Windows.Forms.ComboBox cmbModel;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ComboBox cmbMinf;
        private System.Windows.Forms.ComboBox cmbHoursf;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox cmbMint;
        private System.Windows.Forms.ComboBox cmbHourst;
        private System.Windows.Forms.DateTimePicker dtDatef;
        private System.Windows.Forms.DateTimePicker dtDatet;
        private System.Windows.Forms.Button btnCSV;
        private System.Windows.Forms.Timer timer2;
    }
}