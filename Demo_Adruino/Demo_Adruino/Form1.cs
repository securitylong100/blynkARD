using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Demo_Adruino
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            TfSQL tfSql = new TfSQL();
            string sqlCMBMC = "select distinct machine from adruino";
            tfSql.getComboBoxData(sqlCMBMC, ref cmbMC);
            loadDGV(false, DateTime.Now.ToShortDateString() + " 06:00:00", "");
        }
        public void loadDGV(bool s_date, string dateFrom, string dateTo)
        {
            TfSQL tfSql = new TfSQL();
            string sqlSearch = "select * from adruino where 1=1 ";
            if (s_date)
            {
                sqlSearch += " and date_time >= '" + dateFrom + "' and date_time <= '" + dateTo + "'";
            }
            else { sqlSearch += " and date_time >= '" + dateFrom + "'"; }
            sqlSearch += " order by date_time desc";
            DataTable dt = new DataTable();
            tfSql.sqlDataAdapterFillDatatable(sqlSearch, ref dt);

            dgv.DataSource = dt;

            dgv.Columns["machine"].HeaderText = "Machine";
            dgv.Columns["data_"].HeaderText = "Data";
            dgv.Columns["date_time"].HeaderText = "Date Time";

            if (dgv.RowCount > 0)
            {
                int tong = 0;
                for (int i = 0; i < dgv.RowCount; i++)
                {
                    if(dgv.Rows[i].Cells["data_"].Value.ToString() == "1")
                    {
                        tong++;
                    }
                }
                txtQty.Text = (tong * 6).ToString();
            }
        }

        private void btnSearch_Click(object sender, EventArgs e)
        {
            loadDGV(true, dtpFrom.Value.ToShortDateString() + " 00:00:00",dtpTo.Value.ToShortDateString() + " 23:59:59");
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            runBat();
            loadDGV(false, DateTime.Now.ToShortDateString() + " 06:00:00", "");
        }
        public void runBat()
        {
            if (File.Exists(@"\\192.168.145.7\459qb2\arduino.csv"))
            {
                System.Diagnostics.Process.Start(@"Z:\(00)Public\Software NCVP\adruino\batfile\adruino.bat");
            }
        }
        private void btnLoad_Click(object sender, EventArgs e)
        {
            if (btnLoad.Text == "Auto Load")
            {
                runBat();
                loadDGV(false, DateTime.Now.ToShortDateString() + " 06:00:00", "");
                btnSearch.Enabled = false;
                btnLoad.Text = "Stop";
                if (txtTimer.Text != "")
                {
                    timer1.Interval = int.Parse(txtTimer.Text) * 1000;
                    timer1.Enabled = true;
                }
                else MessageBox.Show("Timer null!","Note", MessageBoxButtons.OK);
                txtTimer.Enabled = false;
            }
            else
            {
                txtTimer.Enabled = true;
                btnSearch.Enabled = true;
                btnLoad.Text = "Auto Load";
                timer1.Enabled = false;
            }            
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }
    }
}
