namespace PQMConnect
{
    partial class IoT_Main_Form

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
            this.cmb_model = new System.Windows.Forms.ComboBox();
            this.lbl_model = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.dtp_from = new System.Windows.Forms.DateTimePicker();
            this.label7 = new System.Windows.Forms.Label();
            this.dtp_to = new System.Windows.Forms.DateTimePicker();
            this.label6 = new System.Windows.Forms.Label();
            this.txt_item_name = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txt_process_name = new System.Windows.Forms.TextBox();
            this.cmb_item_symbol = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cmb_process_symbol = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.cmb_line = new System.Windows.Forms.ComboBox();
            this.lbl_line = new System.Windows.Forms.Label();
            this.dgv_data = new System.Windows.Forms.DataGridView();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btn_search_data = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_data)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // cmb_model
            // 
            this.cmb_model.FormattingEnabled = true;
            this.cmb_model.Location = new System.Drawing.Point(6, 32);
            this.cmb_model.Name = "cmb_model";
            this.cmb_model.Size = new System.Drawing.Size(121, 21);
            this.cmb_model.TabIndex = 0;
            this.cmb_model.SelectedIndexChanged += new System.EventHandler(this.cmb_model_SelectedIndexChanged);
            // 
            // lbl_model
            // 
            this.lbl_model.AutoSize = true;
            this.lbl_model.Location = new System.Drawing.Point(8, 16);
            this.lbl_model.Name = "lbl_model";
            this.lbl_model.Size = new System.Drawing.Size(39, 13);
            this.lbl_model.TabIndex = 1;
            this.lbl_model.Text = "Model:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.dtp_from);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.dtp_to);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.txt_item_name);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.txt_process_name);
            this.groupBox1.Controls.Add(this.cmb_item_symbol);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.cmb_process_symbol);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.cmb_line);
            this.groupBox1.Controls.Add(this.lbl_line);
            this.groupBox1.Controls.Add(this.cmb_model);
            this.groupBox1.Controls.Add(this.lbl_model);
            this.groupBox1.Location = new System.Drawing.Point(4, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(902, 104);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Header";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(204, 60);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(23, 13);
            this.label8.TabIndex = 17;
            this.label8.Text = "To:";
            // 
            // dtp_from
            // 
            this.dtp_from.CustomFormat = "yyyy-MM-dd HH:mm:ss";
            this.dtp_from.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtp_from.Location = new System.Drawing.Point(207, 76);
            this.dtp_from.Name = "dtp_from";
            this.dtp_from.Size = new System.Drawing.Size(150, 20);
            this.dtp_from.TabIndex = 16;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(8, 60);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(33, 13);
            this.label7.TabIndex = 15;
            this.label7.Text = "From:";
            // 
            // dtp_to
            // 
            this.dtp_to.CustomFormat = "yyyy-MM-dd HH:mm:ss";
            this.dtp_to.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtp_to.Location = new System.Drawing.Point(11, 76);
            this.dtp_to.Name = "dtp_to";
            this.dtp_to.Size = new System.Drawing.Size(150, 20);
            this.dtp_to.TabIndex = 14;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(765, 18);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(61, 13);
            this.label6.TabIndex = 13;
            this.label6.Text = "Item Name:";
            // 
            // txt_item_name
            // 
            this.txt_item_name.Location = new System.Drawing.Point(759, 34);
            this.txt_item_name.Name = "txt_item_name";
            this.txt_item_name.Size = new System.Drawing.Size(121, 20);
            this.txt_item_name.TabIndex = 12;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(464, 17);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(79, 13);
            this.label5.TabIndex = 11;
            this.label5.Text = "Process Name:";
            // 
            // txt_process_name
            // 
            this.txt_process_name.Location = new System.Drawing.Point(458, 33);
            this.txt_process_name.Name = "txt_process_name";
            this.txt_process_name.Size = new System.Drawing.Size(121, 20);
            this.txt_process_name.TabIndex = 10;
            // 
            // cmb_item_symbol
            // 
            this.cmb_item_symbol.FormattingEnabled = true;
            this.cmb_item_symbol.Location = new System.Drawing.Point(617, 33);
            this.cmb_item_symbol.Name = "cmb_item_symbol";
            this.cmb_item_symbol.Size = new System.Drawing.Size(121, 21);
            this.cmb_item_symbol.TabIndex = 6;
            this.cmb_item_symbol.SelectedIndexChanged += new System.EventHandler(this.cmb_item_symbol_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(619, 17);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Item symbol:";
            // 
            // cmb_process_symbol
            // 
            this.cmb_process_symbol.FormattingEnabled = true;
            this.cmb_process_symbol.Location = new System.Drawing.Point(316, 31);
            this.cmb_process_symbol.Name = "cmb_process_symbol";
            this.cmb_process_symbol.Size = new System.Drawing.Size(121, 21);
            this.cmb_process_symbol.TabIndex = 4;
            this.cmb_process_symbol.SelectedIndexChanged += new System.EventHandler(this.cmb_process_symbol_SelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(318, 15);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(83, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Process symbol:";
            // 
            // cmb_line
            // 
            this.cmb_line.FormattingEnabled = true;
            this.cmb_line.Location = new System.Drawing.Point(160, 32);
            this.cmb_line.Name = "cmb_line";
            this.cmb_line.Size = new System.Drawing.Size(121, 21);
            this.cmb_line.TabIndex = 2;
            this.cmb_line.SelectedIndexChanged += new System.EventHandler(this.cmb_line_SelectedIndexChanged);
            // 
            // lbl_line
            // 
            this.lbl_line.AutoSize = true;
            this.lbl_line.Location = new System.Drawing.Point(162, 16);
            this.lbl_line.Name = "lbl_line";
            this.lbl_line.Size = new System.Drawing.Size(30, 13);
            this.lbl_line.TabIndex = 3;
            this.lbl_line.Text = "Line:";
            // 
            // dgv_data
            // 
            this.dgv_data.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgv_data.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.dgv_data.Location = new System.Drawing.Point(0, 203);
            this.dgv_data.Name = "dgv_data";
            this.dgv_data.Size = new System.Drawing.Size(1165, 404);
            this.dgv_data.TabIndex = 3;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btn_search_data);
            this.groupBox2.Location = new System.Drawing.Point(4, 113);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(902, 60);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Process:";
            // 
            // btn_search_data
            // 
            this.btn_search_data.Location = new System.Drawing.Point(11, 19);
            this.btn_search_data.Name = "btn_search_data";
            this.btn_search_data.Size = new System.Drawing.Size(75, 34);
            this.btn_search_data.TabIndex = 0;
            this.btn_search_data.Text = "Search";
            this.btn_search_data.UseVisualStyleBackColor = true;
            this.btn_search_data.Click += new System.EventHandler(this.btn_search_data_Click);
            // 
            // IoT_Main_Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1165, 607);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.dgv_data);
            this.Controls.Add(this.groupBox1);
            this.Name = "IoT_Main_Form";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.IoT_Main_Form_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_data)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox cmb_model;
        private System.Windows.Forms.Label lbl_model;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.DateTimePicker dtp_from;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.DateTimePicker dtp_to;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txt_item_name;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txt_process_name;
        private System.Windows.Forms.ComboBox cmb_item_symbol;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cmb_process_symbol;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cmb_line;
        private System.Windows.Forms.Label lbl_line;
        private System.Windows.Forms.DataGridView dgv_data;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btn_search_data;
    }
}

