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
        public string content = "long";
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
            led("5", btn_rl05);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            led("6", btn_rl06);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            led("7", btn_rl07);
        }
        private void btn_rl4_Click(object sender, EventArgs e)
        {
            led("8", btn_rl08);//do relay 4: hoạc 5 hoạc 5 Ng, 6 Ok
        }
        private void btn_rl03_Click(object sender, EventArgs e)
        {
            led("3", btn_rl03);
        }

        private void btn_rl04_Click(object sender, EventArgs e)
        {
            led("4", btn_rl04);
        }

        private void btn_rl02_Click(object sender, EventArgs e)
        {
            led("2", btn_rl02);
        }

        private void btn_rl13_Click(object sender, EventArgs e)
        {
            led("1", btn_rl13);
        }
        //  void led(string sang, string tat,Button btn_led)
        void led(string sang, Button btn_led)
        {
            {
                serialcom.Write(sang);
            }
        }
      
        private void serialcom_DataReceived_1(object sender, SerialDataReceivedEventArgs e)
        {
            content = "";
            content = serialcom.ReadLine().ToString();
            serialcom.Encoding = Encoding.ASCII;
        }

        private void btn_tcpip_Click(object sender, EventArgs e)
        {
            // this.Close();
            Wifi_Form wififrm = new Wifi_Form();
            wififrm.ShowDialog();
        }

        private void btn_valrw_Click(object sender, EventArgs e)
        {
            lbl_valrw.Text = content;
        }

     
      
    }
}
