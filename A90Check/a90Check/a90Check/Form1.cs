using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace a90Check
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            LoadInfo();
        }
        public void LoadInfo()
        {
            if (!Directory.Exists(@"C:\GA1")) { Directory.CreateDirectory(@"C:\GA1"); }
            if (!File.Exists(@"C:\GA1\info.txt")) { File.Create(@"C:\GA1\info.txt"); }
            var reader = new StreamReader(@"C:\GA1\info.txt");
            var s = reader.ReadLine();
            string[] va = s.Split('"').ToArray();
            lbl_line.Text = va[3];
            lbl_model.Text = va[1];
            reader.Close();

        }
        private void btn_check_Click(object sender, EventArgs e)
        {
            if (txt_barcodeCheck.Text != "")
            {
                LoadDGV(dgvCheck, txt_barcodeCheck.Text, false);
                TfSQL con = new TfSQL();
                string sql_thurst = "select a90_status from t_checkpusha90main where  a90_barcode = '" + txt_barcodeCheck.Text + "' order by a90_id desc limit 1";
                string sql_noise = "select a90_noise_status from t_checkpusha90main where  a90_barcode = '" + txt_barcodeCheck.Text + "' order by a90_id desc limit 1";
                string thurst_status = con.sqlExecuteScalarString(sql_thurst);
                string noise_status = con.sqlExecuteScalarString(sql_noise);
                if (thurst_status == "OK")
                {
                    btn_thurststatus.Text = "OK";
                    btn_thurststatus.BackColor = Color.Green;
                    txt_barcodeCheck.Text = "";
                }
                else if (thurst_status == "NG")
                {
                    btn_thurststatus.Text = "NG";
                    btn_thurststatus.BackColor = Color.Red;
                    txt_barcodeCheck.Text = "";
                }
                if (noise_status == "OK")
                {
                    btn_noisestatus.Text = "OK";
                    btn_noisestatus.BackColor = Color.Green;
                    txt_barcodeCheck.Text = "";
                }
                else if (noise_status == "NG")
                {
                    btn_noisestatus.Text = "NG";
                    btn_noisestatus.BackColor = Color.Red;
                    txt_barcodeCheck.Text = "";
                }
                if (thurst_status == "")
                {
                    btn_thurststatus.Text = "WAITING";
                    txt_barcodeCheck.Text = "";
                }
                if (noise_status == "")
                {
                    btn_noisestatus.Text = "WAITING";
                    txt_barcodeCheck.Text = "";
                }
            }
            else
            {
                MessageBox.Show("Barocde No is Null <Chưa nhập Barcode>", "Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
                btn_thurststatus.Text = "WAITING";
                btn_thurststatus.BackColor = SystemColors.Control;
                btn_noisestatus.Text = "WAITING";
                btn_noisestatus.BackColor = SystemColors.Control;
            }
        }

        public void LoadDGV(DataGridView datagv, string barcode, bool order)
        {
            TfSQL tf = new TfSQL();
            DataTable dt = new DataTable();
            string sqlDGV = "select a90_barcode, a90_status, a90_noise_status, a90_datetime  from t_checkpusha90main where a90_barcode = '" + barcode + "' ";

            if (order) { sqlDGV += "order by a90_datetime desc limit 1"; }
            else { sqlDGV += "order by a90_datetime desc"; }

            tf.sqlDataAdapterFillDatatable(sqlDGV, ref dt);
            datagv.DataSource = dt;

            if (datagv.RowCount > 0)
            {
                datagv.Columns["a90_barcode"].HeaderText = "Barcode";
                datagv.Columns["a90_status"].HeaderText = "Thurst Status ";
                datagv.Columns["a90_datetime"].HeaderText = "DateTime";
                datagv.Columns["a90_noise_status"].HeaderText = "Noise Status";
            }
            datagv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
        }

        private void btn_status_MouseClick(object sender, MouseEventArgs e)
        {
            AddStatus(e);
        }
        private void tabPage1_MouseClick(object sender, MouseEventArgs e)
        {
            AddStatus(e);
        }
        public void AddStatus(MouseEventArgs e)
        {
            if (login)
            {
                if (txt_barcode.Text.Trim() != "")
                {
                    string status = "";
                    if (e.Button == MouseButtons.Right)
                    {
                        status = "NG";
                        btn_status.Text = "NG";
                        btn_status.BackColor = Color.Red;
                    }
                    if (e.Button == MouseButtons.Left)
                    {
                        status = "OK";
                        btn_status.Text = "OK";
                        btn_status.BackColor = Color.Green;
                    }
                    TfSQL tf = new TfSQL();
                    string sqlInsert = "insert into t_checkpusha90main(a90_model, a90_line, a90_barcode, a90_status, a90_datetime ,a90_factory) ";
                    sqlInsert += "values('" + lbl_model.Text + "','" + lbl_line.Text + "','" + txt_barcode.Text + "','" + status + "', now(),'NCVP')";
                    if (tf.sqlExecuteNonQuery(sqlInsert, false))
                    {
                        LoadDGV(dgv, txt_barcode.Text, true);
                        txt_barcode.Text = null;
                        txt_barcode.SelectNextControl(txt_barcode, true, false, true, true);
                        timer1.Interval = int.Parse(txtTimer.Text) * 1000;
                        timer1.Enabled = true;
                    }
                    else dgv.DataSource = null;
                }
                else return;
            }
            else
            {
                MessageBox.Show("Not Login <Chưa đăng nhập> ", "Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            btn_status.Text = "Waiting";
            btn_status.BackColor = SystemColors.Control;
            dgv.DataSource = null;
            timer1.Enabled = false;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            timer1.Enabled = false;
            timerData.Enabled = false;
        }

        private void txt_barcode_MouseClick(object sender, MouseEventArgs e)
        {
            AddStatus(e);
        }

        private void txtTimer_TextChanged(object sender, EventArgs e)
        {

        }
        string sqlExport;
        private void btnExport_Click(object sender, EventArgs e)
        {
            //TfSQL tf = new TfSQL();
            //string sqlExport = "select a90_barcode Barcode, a90_status status, a90_datetime DateTime from t_checkpusha90main where a90_datetime > '" + dtpFrom.Value.ToString() + "' and a90_datetime < '" + dtpTo.Value.ToString() + "' order by a90_datetime desc";
            //DataTable dt = new DataTable();

            //tf.sqlDataAdapterFillDatatable(sqlExport, ref dt);
            if (dtdata != null)
            {
                ExcelClass ex = new ExcelClass();
                ex.ExportToExcel(dtdata);

            }
        }

        private void txtTimer_KeyPress(object sender, KeyPressEventArgs e)
        {

        }
        public DataTable dtdata;
        private void btnView_Click(object sender, EventArgs e)
        {
            TfSQL tf = new TfSQL();
            string sqlExport = "select row_number() over(order by a90_datetime desc) stt, a90_model Model, a90_line line, a90_barcode Barcode, a90_status ThurstStatus, a90_noise_status as NoiseStatus ,a90_datetime DateTime from t_checkpusha90main where a90_datetime > '" + dtpFrom.Value.ToString() + "' and a90_datetime < '" + dtpTo.Value.ToString() + "' order by a90_datetime desc";
            dtdata = new DataTable();

            tf.sqlDataAdapterFillDatatable(sqlExport, ref dtdata);
            dgvData.DataSource = dtdata;
            dgvData.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dgvData.Columns["stt"].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;

            if (dgvData.RowCount > 0)
            {
                for (int i = 0; i < dgvData.RowCount; i++)
                {
                    if (dgvData.Rows[i].Cells["ThurstStatus"].Value.ToString() == "NG")
                    {
                        dgvData.Rows[i].Cells["ThurstStatus"].Style.BackColor = Color.Red;
                    }
                    if (dgvData.Rows[i].Cells["NoiseStatus"].Value.ToString() == "NG")
                    {
                        dgvData.Rows[i].Cells["NoiseStatus"].Style.BackColor = Color.Red;
                    }
                }
            }
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            if (btnLoad.Text == "Load")
            {
                LoadData();
                timerData.Enabled = true;
                btnLoad.Text = "Stop";
            }
            else if (btnLoad.Text == "Stop")
            {
                btnLoad.Text = "Load";
                timerData.Enabled = false;
            }
        }

        private void timerData_Tick(object sender, EventArgs e)
        {
            LoadData();
            timeleft();
        }
        void timeleft()
        {
            if (dgvData.RowCount > 3 && txt_plan.Text != "")
            {
                DateTime b = DateTime.Parse(dgvData.Rows[0].Cells["DateTime"].Value.ToString());
                DateTime a = DateTime.Parse(dgvData.Rows[dgvData.RowCount - 1].Cells["DateTime"].Value.ToString());
                TimeSpan c = (b - a);
                string[] time = c.ToString().Split(':').ToArray();
                int hour = int.Parse(time[0].Substring(time[0].Length - 2, 2));
                int minues = int.Parse(time[1]);
                int second = int.Parse(time[2]);
                string[] stringday = c.ToString().Split('.').ToArray();
                int day = int.Parse(stringday[0]);
                int totalsecond = day * 24 * 60 * 60 + hour * 60 * 60 + minues * 60 + second;
                int pcssecond = totalsecond / (dgvData.RowCount);
                int needtimesecond =( int.Parse(txt_plan.Text)-(dgvData.RowCount)) * pcssecond;
                if (needtimesecond < 0) { lbl_resulf.Text = "0s ~ " + 0 + " days " + 0 + " hours " + 0 + " minues "; return; };
                int dayout = needtimesecond / (24 * 60 * 60);
                int hourout = (needtimesecond - (dayout * 24 * 60 * 60)) / (60 * 60);
                int minuesout = (needtimesecond - (dayout * 24 * 60 * 60) - (hourout * 60 * 60)) / 60;
                lbl_resulf.Text = needtimesecond.ToString() + "s ~ " + dayout + " days " + hourout + " hours " + minuesout + " minues ";
            }
        }
        public void LoadData()
        {
            TfSQL tf = new TfSQL();
            string sqlExport = "select row_number() over(order by a90_datetime desc) stt, a90_model Model, a90_line line, a90_barcode Barcode, a90_status ThurstStatus,a90_noise_status as NoiseStatus, a90_datetime DateTime from t_checkpusha90main where a90_datetime > '" + dtpFrom.Value.ToString() + "' order by a90_datetime desc";
            DataTable dt = new DataTable();

            tf.sqlDataAdapterFillDatatable(sqlExport, ref dt);
            dgvData.DataSource = dt;
            dgvData.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dgvData.Columns["stt"].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;

            if (dgvData.RowCount > 0)
            {
                for (int i = 0; i < dgvData.RowCount; i++)
                {
                    if (dgvData.Rows[i].Cells["ThurstStatus"].Value.ToString() == "NG")
                    {
                        dgvData.Rows[i].Cells["ThurstStatus"].Style.BackColor = Color.Red;
                    }
                    if (dgvData.Rows[i].Cells["NoiseStatus"].Value.ToString() == "NG")
                    {
                        dgvData.Rows[i].Cells["NoiseStatus"].Style.BackColor = Color.Red;
                    }
                }
            }
        }
        private void chk_CheckedChanged(object sender, EventArgs e)
        {
            //if (chk.Checked)
            //{
            //    Pass pa = new Pass();
            //    pa.ShowDialog();
            //}
        }
        public bool login = false;

        private void chk_Click(object sender, EventArgs e)
        {
            logincheck(chk);
        }
        private void chk_NC_Click(object sender, EventArgs e)
        {
            logincheck(chk_NC);
        }
        void logincheck(CheckBox checkbox)
        {
            if (checkbox.Checked)
            {
                Pass pa = new Pass(this);
                pa.ShowDialog();
                if (login == true)
                {
                    checkbox.Checked = true;
                }
                else checkbox.Checked = false;
            }
            else login = false;
        }



        public void LoadDGVNoise(DataGridView datagv, string barcode, bool order)
        {
            TfSQL tf = new TfSQL();
            DataTable dt = new DataTable();
            string sqlDGV = "select a90_model, a90_line, a90_barcode, a90_status, a90_datetime from t_checkpusha90main where a90_barcode = '" + barcode + "' ";

            if (order) { sqlDGV += "order by a90_datetime desc limit 1"; }
            else { sqlDGV += "order by a90_datetime desc"; }

            tf.sqlDataAdapterFillDatatable(sqlDGV, ref dt);
            datagv.DataSource = dt;

            if (datagv.RowCount > 0)
            {
                datagv.Columns["a90_barcode"].HeaderText = "Barcode";
                datagv.Columns["a90_status"].HeaderText = "Status";
                datagv.Columns["a90_datetime"].HeaderText = "DateTime";
            }
            datagv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
        }
        public void UpdateStatusNoise(MouseEventArgs e)
        {
            if (login)
            {
                if (txtBarcodeNoise.Text.Trim() != "")
                {
                    TfSQL tf = new TfSQL();
                    string sqlcheckbarcode = "select count(*) from t_checkpusha90main where a90_barcode = '" + txtBarcodeNoise.Text + "'";
                    int checkbarcode = int.Parse(tf.sqlExecuteScalarString(sqlcheckbarcode));
                    if (checkbarcode > 0)
                    {
                        string status = "";
                        if (e.Button == MouseButtons.Right)
                        {
                            status = "NG";
                            btnStatusNoise.Text = "NG";
                            btnStatusNoise.BackColor = Color.Red;
                        }
                        if (e.Button == MouseButtons.Left)
                        {
                            status = "OK";
                            btnStatusNoise.Text = "OK";
                            btnStatusNoise.BackColor = Color.Green;
                        }
                        string sqlUpdate = "update t_checkpusha90main set a90_noise_status = '" + status + "' where a90_barcode = '" + txtBarcodeNoise.Text + "'";
                        if (tf.sqlExecuteNonQuery(sqlUpdate, false))
                        {
                            LoadDGV(dgvNoise, txtBarcodeNoise.Text, true);
                            txtBarcodeNoise.Text = null;
                            txtBarcodeNoise.SelectNextControl(txtBarcodeNoise, true, false, true, true); //trả lại con chỏ vô textbox
                            timerNoise.Interval = int.Parse(txtTimerNoise.Text) * 1000;
                            timerNoise.Enabled = true;
                        }
                        else dgvNoise.DataSource = null;
                    }
                    else
                    {
                        MessageBox.Show("Barocde No is Null <Không có Mã barcode này >", "Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
                    }
                }
                else return;
            }
            else
            {
                MessageBox.Show("Not Login <Chưa đăng nhập> ", "Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
            }
        }
        private void tabNoise_MouseClick(object sender, MouseEventArgs e)
        {
            UpdateStatusNoise(e);
        }

        private void timerNoise_Tick(object sender, EventArgs e)
        {
            btnStatusNoise.Text = "Waiting";
            btnStatusNoise.BackColor = SystemColors.Control;
            dgvNoise.DataSource = null;
            timerNoise.Enabled = false;
        }

    }
}
