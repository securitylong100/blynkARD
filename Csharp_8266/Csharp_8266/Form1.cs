using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
namespace Csharp_8266
{
    public partial class Form1 : Form
    {
        public string content;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            cmb_com.DataSource = SerialPort.GetPortNames();
        }

        private void btn_ketnoi_Click(object sender, EventArgs e)
        {
            if (btn_ketnoi.Text == "Đang Ngắt Kết Nối")
            {
                if (!serialcom.IsOpen) 
                {

                    serialcom.PortName = cmb_com.Text;
                    serialcom.Open();
                    btn_ketnoi.Text = "Kết Nối";
                }
            }
            else if (btn_ketnoi.Text == "Kết Nối")
            {
                serialcom.Close();
                btn_ketnoi.Text = "Đang Ngắt Kết Nối";
            }

        }

        private void btn_led_Click(object sender, EventArgs e)
        {
            if (btn_led.Text == "Đang Sáng")
            {
                serialcom.Write("1");
                btn_led.Text = "Đã Tắt";
                btn_led.BackColor = SystemColors.Control;
            }
            else if (btn_led.Text == "Đã Tắt")
            {
                serialcom.Write("0");
                btn_led.Text = "Đang Sáng";
                btn_led.BackColor = Color.Red;
            }

        }
        string atam = "";
        private void serialcom_DataReceived_1(object sender, SerialDataReceivedEventArgs e)
        {
             
           
           // Thread.Sleep(1000);
            serialcom.Encoding = Encoding.ASCII;
            content = serialcom.ReadExisting();
            atam = content;
        }

        private void btn_tcpip_Click(object sender, EventArgs e)
        {
           // this.Close();
            Wifi_Form wififrm = new Wifi_Form();            
            wififrm.ShowDialog();
        }
    }
}
