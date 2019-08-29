namespace Csharp_8266
{
    partial class Form1
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
            this.label1 = new System.Windows.Forms.Label();
            this.cmb_com = new System.Windows.Forms.ComboBox();
            this.btn_ketnoi = new System.Windows.Forms.Button();
            this.btn_rl05 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.serialcom = new System.IO.Ports.SerialPort(this.components);
            this.label3 = new System.Windows.Forms.Label();
            this.btn_rl06 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.btn_rl07 = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.btn_rl08 = new System.Windows.Forms.Button();
            this.btn_valrw = new Com.Nidec.Mes.Framework.ButtonCommon();
            this.lbl_valrw = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.btn_rl13 = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.btn_rl02 = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.btn_rl04 = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.btn_rl03 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(79, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(84, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Chọn Cổng Com";
            // 
            // cmb_com
            // 
            this.cmb_com.FormattingEnabled = true;
            this.cmb_com.Location = new System.Drawing.Point(75, 46);
            this.cmb_com.Name = "cmb_com";
            this.cmb_com.Size = new System.Drawing.Size(98, 21);
            this.cmb_com.TabIndex = 1;
            // 
            // btn_ketnoi
            // 
            this.btn_ketnoi.Location = new System.Drawing.Point(192, 46);
            this.btn_ketnoi.Name = "btn_ketnoi";
            this.btn_ketnoi.Size = new System.Drawing.Size(127, 23);
            this.btn_ketnoi.TabIndex = 2;
            this.btn_ketnoi.Text = "Đang Ngắt Kết Nối";
            this.btn_ketnoi.UseVisualStyleBackColor = true;
            this.btn_ketnoi.Click += new System.EventHandler(this.btn_ketnoi_Click);
            // 
            // btn_rl05
            // 
            this.btn_rl05.Location = new System.Drawing.Point(192, 92);
            this.btn_rl05.Name = "btn_rl05";
            this.btn_rl05.Size = new System.Drawing.Size(82, 23);
            this.btn_rl05.TabIndex = 3;
            this.btn_rl05.Text = "RL5";
            this.btn_rl05.UseVisualStyleBackColor = true;
            this.btn_rl05.Click += new System.EventHandler(this.btn_led_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(90, 97);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Trang Thái RL5";
            // 
            // serialcom
            // 
            this.serialcom.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialcom_DataReceived_1);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(90, 139);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(82, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Trang Thái RL6";
            // 
            // btn_rl06
            // 
            this.btn_rl06.Location = new System.Drawing.Point(192, 134);
            this.btn_rl06.Name = "btn_rl06";
            this.btn_rl06.Size = new System.Drawing.Size(82, 23);
            this.btn_rl06.TabIndex = 6;
            this.btn_rl06.Text = "RL6";
            this.btn_rl06.UseVisualStyleBackColor = true;
            this.btn_rl06.Click += new System.EventHandler(this.button1_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(90, 181);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(82, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Trang Thái RL7";
            // 
            // btn_rl07
            // 
            this.btn_rl07.Location = new System.Drawing.Point(192, 176);
            this.btn_rl07.Name = "btn_rl07";
            this.btn_rl07.Size = new System.Drawing.Size(82, 23);
            this.btn_rl07.TabIndex = 8;
            this.btn_rl07.Text = "RL7";
            this.btn_rl07.UseVisualStyleBackColor = true;
            this.btn_rl07.Click += new System.EventHandler(this.button2_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(90, 221);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(82, 13);
            this.label5.TabIndex = 11;
            this.label5.Text = "Trang Thái RL8";
            // 
            // btn_rl08
            // 
            this.btn_rl08.Location = new System.Drawing.Point(192, 216);
            this.btn_rl08.Name = "btn_rl08";
            this.btn_rl08.Size = new System.Drawing.Size(82, 23);
            this.btn_rl08.TabIndex = 10;
            this.btn_rl08.Text = "RL8";
            this.btn_rl08.UseVisualStyleBackColor = true;
            this.btn_rl08.Click += new System.EventHandler(this.btn_rl4_Click);
            // 
            // btn_valrw
            // 
            this.btn_valrw.BackColor = System.Drawing.SystemColors.Control;
            this.btn_valrw.ControlId = null;
            this.btn_valrw.Font = new System.Drawing.Font("Arial", 9F);
            this.btn_valrw.Location = new System.Drawing.Point(412, 161);
            this.btn_valrw.Name = "btn_valrw";
            this.btn_valrw.Size = new System.Drawing.Size(80, 33);
            this.btn_valrw.TabIndex = 12;
            this.btn_valrw.Text = "VALRW";
            this.btn_valrw.UseVisualStyleBackColor = false;
            this.btn_valrw.Click += new System.EventHandler(this.btn_valrw_Click);
            // 
            // lbl_valrw
            // 
            this.lbl_valrw.AutoSize = true;
            this.lbl_valrw.Location = new System.Drawing.Point(329, 97);
            this.lbl_valrw.Name = "lbl_valrw";
            this.lbl_valrw.Size = new System.Drawing.Size(35, 13);
            this.lbl_valrw.TabIndex = 14;
            this.lbl_valrw.Text = "label6";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(90, 385);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(88, 13);
            this.label6.TabIndex = 22;
            this.label6.Text = "Trang Thái RL13";
            // 
            // btn_rl13
            // 
            this.btn_rl13.Location = new System.Drawing.Point(192, 380);
            this.btn_rl13.Name = "btn_rl13";
            this.btn_rl13.Size = new System.Drawing.Size(82, 23);
            this.btn_rl13.TabIndex = 21;
            this.btn_rl13.Text = "RL13";
            this.btn_rl13.UseVisualStyleBackColor = true;
            this.btn_rl13.Click += new System.EventHandler(this.btn_rl13_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(90, 345);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(82, 13);
            this.label7.TabIndex = 20;
            this.label7.Text = "Trang Thái RL2";
            // 
            // btn_rl02
            // 
            this.btn_rl02.Location = new System.Drawing.Point(192, 340);
            this.btn_rl02.Name = "btn_rl02";
            this.btn_rl02.Size = new System.Drawing.Size(82, 23);
            this.btn_rl02.TabIndex = 19;
            this.btn_rl02.Text = "RL2";
            this.btn_rl02.UseVisualStyleBackColor = true;
            this.btn_rl02.Click += new System.EventHandler(this.btn_rl02_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(90, 303);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(82, 13);
            this.label8.TabIndex = 18;
            this.label8.Text = "Trang Thái RL4";
            // 
            // btn_rl04
            // 
            this.btn_rl04.Location = new System.Drawing.Point(192, 298);
            this.btn_rl04.Name = "btn_rl04";
            this.btn_rl04.Size = new System.Drawing.Size(82, 23);
            this.btn_rl04.TabIndex = 17;
            this.btn_rl04.Text = "RL4";
            this.btn_rl04.UseVisualStyleBackColor = true;
            this.btn_rl04.Click += new System.EventHandler(this.btn_rl04_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(90, 261);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(82, 13);
            this.label9.TabIndex = 16;
            this.label9.Text = "Trang Thái RL3";
            // 
            // btn_rl03
            // 
            this.btn_rl03.Location = new System.Drawing.Point(192, 256);
            this.btn_rl03.Name = "btn_rl03";
            this.btn_rl03.Size = new System.Drawing.Size(82, 23);
            this.btn_rl03.TabIndex = 15;
            this.btn_rl03.Text = "RL3";
            this.btn_rl03.UseVisualStyleBackColor = true;
            this.btn_rl03.Click += new System.EventHandler(this.btn_rl03_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(668, 415);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.btn_rl13);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.btn_rl02);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.btn_rl04);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.btn_rl03);
            this.Controls.Add(this.lbl_valrw);
            this.Controls.Add(this.btn_valrw);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.btn_rl08);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.btn_rl07);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.btn_rl06);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btn_rl05);
            this.Controls.Add(this.btn_ketnoi);
            this.Controls.Add(this.cmb_com);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Com and Led";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cmb_com;
        private System.Windows.Forms.Button btn_ketnoi;
        private System.Windows.Forms.Button btn_rl05;
        private System.Windows.Forms.Label label2;
        private System.IO.Ports.SerialPort serialcom;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btn_rl06;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btn_rl07;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button btn_rl08;
        private Com.Nidec.Mes.Framework.ButtonCommon btn_valrw;
        private System.Windows.Forms.Label lbl_valrw;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btn_rl13;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button btn_rl02;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button btn_rl04;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button btn_rl03;
    }
}

