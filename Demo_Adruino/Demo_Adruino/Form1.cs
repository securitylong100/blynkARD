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
using System.Windows.Forms.DataVisualization.Charting;

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
            ShowChartOutput();
        }
        public void ShowChartOutput()
        {
            if(dgv.RowCount >8)
            {
                DateTime b = DateTime.Parse(dgv.Rows[0].Cells["date_time"].Value.ToString());
                DateTime a = DateTime.Parse(dgv.Rows[dgv.RowCount - 1].Cells["date_time"].Value.ToString());
                TimeSpan c = (b - a);

            }

            /*
            chart_output.ResetAutoValues();
            chart_output.ResumeLayout();
            chart_output.Series.Clear();
            chart_output.Titles[0].Text = "CHART SHOW OUTPUT DATA";
            chart_output.Titles[0].Font = new Font("Arial", 16, FontStyle.Bold);
            chart_output.ChartAreas[0].AxisX.LabelStyle.Format = "dd-MM HH:mm";
            chart_output.ChartAreas[0].AxisX.MajorGrid.Enabled = false;
            chart_output.ChartAreas[0].AxisX.IntervalAutoMode = IntervalAutoMode.VariableCount;
            chart_output.ChartAreas[0].AxisX.LabelStyle.Angle = -60;
            chart_output.ChartAreas[0].AxisY.Title = "OUTPUT [PCS]";

            chart_output.Series.Add("Output");
            chart_output.Series["Output"].XValueType = ChartValueType.Date;
            chart_output.Series["Output"].ChartType = SeriesChartType.Line;
            chart_output.Series["Output"].Color = Color.FromArgb(0, 192, 0); //blue
            chart_output.Series["Output"].XValueMember = "date_time";
            chart_output.Series["Output"].YValueMembers = "data_";
            chart_output.Series["Output"].IsValueShownAsLabel = true;
            chart_output.DataSource = dgv.DataSource;
            chart_output.DataBind();
            //end chart
            */
        }
        private void btnSearch_Click(object sender, EventArgs e)
        {
            loadDGV(true, dtpFrom.Value.ToString(),dtpTo.Value.ToString());
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            runBat();
            loadDGV(false, dtpFrom.Value.ToString(), "");
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
                loadDGV(false, dtpFrom.Value.ToString(), "");
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
