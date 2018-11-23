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
            this.btn_led = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.serialcom = new System.IO.Ports.SerialPort(this.components);
            this.btn_tcpip = new System.Windows.Forms.Button();
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
            // btn_led
            // 
            this.btn_led.Location = new System.Drawing.Point(192, 92);
            this.btn_led.Name = "btn_led";
            this.btn_led.Size = new System.Drawing.Size(127, 23);
            this.btn_led.TabIndex = 3;
            this.btn_led.Text = "Đã Tắt";
            this.btn_led.UseVisualStyleBackColor = true;
            this.btn_led.Click += new System.EventHandler(this.btn_led_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(90, 97);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Trang Thái Led:";
            // 
            // serialcom
            // 
            this.serialcom.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialcom_DataReceived_1);
            // 
            // btn_tcpip
            // 
            this.btn_tcpip.Location = new System.Drawing.Point(192, 139);
            this.btn_tcpip.Name = "btn_tcpip";
            this.btn_tcpip.Size = new System.Drawing.Size(127, 23);
            this.btn_tcpip.TabIndex = 5;
            this.btn_tcpip.Text = "TCP/IP wifi==>> ";
            this.btn_tcpip.UseVisualStyleBackColor = true;
            this.btn_tcpip.Click += new System.EventHandler(this.btn_tcpip_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(451, 189);
            this.Controls.Add(this.btn_tcpip);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btn_led);
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
        private System.Windows.Forms.Button btn_led;
        private System.Windows.Forms.Label label2;
        private System.IO.Ports.SerialPort serialcom;
        private System.Windows.Forms.Button btn_tcpip;
    }
}

