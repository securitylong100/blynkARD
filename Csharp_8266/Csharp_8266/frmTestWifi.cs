using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace Csharp_8266
{
    public partial class frmTestWifi : Form
    {
        int port;
        int k;
        public frmTestWifi()
        {
            InitializeComponent();
            lbServerName.Text = Dns.GetHostName();
            IPHostEntry hostname = Dns.GetHostByName(lbServerName.Text);
            IPAddress[] IP = hostname.AddressList;
            lbIP.Text = IP[0].ToString();
            port = 3235;
            k = 0;
        }

        public void run(IPAddress localIP)
        {
            TcpListener slistener = new TcpListener(localIP, port);
            slistener.Start();
            for (; ;)
            {
                Socket socketforclient = slistener.AcceptSocket();
                if(socketforclient.Connected)
                {
                    send(socketforclient, k);
                    socketforclient.Close();
                    break;
                }
            }
        }

        public void send(Socket socketforclient, int k)
        {
            NetworkStream stream = new NetworkStream(socketforclient);
            System.IO.StreamWriter wr = new System.IO.StreamWriter(stream);
            wr.Write(k);
            wr.Flush();
            wr.Close();
            stream.Close();
        }

        private void btnOn_Click(object sender, EventArgs e)
        {
            k = 1;
            IPAddress localIP = IPAddress.Parse(lbIP.Text);
            this.run(localIP);
        }

        private void btnOff_Click(object sender, EventArgs e)
        {
            k = 0;
            IPAddress localIP = IPAddress.Parse(lbIP.Text);
            this.run(localIP);
        }
    }
}
