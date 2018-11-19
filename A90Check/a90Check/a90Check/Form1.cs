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
            TfSQL con = new TfSQL();
            AcceptButton = btn_check;
            string sqlModel = "select distinct model_name from t_model ";
            string sqlLine = "select distinct line_name from t_line ";
            con.getComboBoxData(sqlModel, ref cmbModel);
            con.getComboBoxData(sqlLine, ref cmbLine);
            if (txt_barcode.Text != null)
            {


            }
        }
        private void btn_check_Click(object sender, EventArgs e)
        {
            if (txt_barcode2.Text != "")
            {
                LoadDGV(dgvCheck, txt_barcode2.Text, false);
                TfSQL con = new TfSQL();
                string sql = "select a90_status from t_checkpusha90main where  a90_barcode = '" + txt_barcode2.Text + "' order by a90_id desc limit 1";
                string status = con.sqlExecuteScalarString(sql);
                if (status == "OK")
                {
                    btn_status2.Text = "OK";
                    btn_status2.BackColor = Color.Green;
                    txt_barcode2.Text = "";
                }
                else if (status == "NG")
                {
                    btn_status2.Text = "NG";
                    btn_status2.BackColor = Color.Red;
                    txt_barcode2.Text = "";
                }
                else
                {
                    MessageBox.Show("Barcode is not found <Không tìm thấy mã barcode này", "Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
                    btn_status2.Text = "WAITING";
                    txt_barcode2.Text = "";
                }
            }
            else
            {
                MessageBox.Show("Barocde No is Null <Chưa nhập Barcode>", "Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
                btn_status2.Text = "WAITING";

                btn_status2.BackColor = SystemColors.Control;

            }
        }

        public void LoadDGV(DataGridView datagv,string barcode, bool order)
        {
            TfSQL tf = new TfSQL();
            DataTable dt = new DataTable();
            string sqlDGV = "select a90_barcode, a90_status, a90_datetime from t_checkpusha90main where a90_barcode = '" + barcode + "' ";

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
                    sqlInsert += "values('" + cmbModel.Text + "','" + cmbLine.Text + "','" + txt_barcode.Text + "','" + status + "', now(),'NCVP')";
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
            if(dtdata != null)
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
            string sqlExport = "select row_number() over(order by a90_datetime desc) stt, a90_model Model, a90_line line, a90_barcode Barcode, a90_status status, a90_datetime DateTime from t_checkpusha90main where a90_datetime > '" + dtpFrom.Value.ToString() + "' and a90_datetime < '" + dtpTo.Value.ToString() +  "' order by a90_datetime desc";
            dtdata = new DataTable();

            tf.sqlDataAdapterFillDatatable(sqlExport, ref dtdata);
            dgvData.DataSource = dtdata;
            dgvData.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dgvData.Columns["stt"].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;

            if (dgvData.RowCount > 0)
            {
                for (int i = 0; i < dgvData.RowCount; i++)
                {
                    if (dgvData.Rows[i].Cells["status"].Value.ToString() == "NG")
                    {
                        dgvData.Rows[i].Cells["status"].Style.BackColor = Color.Red;
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
        }
        public void LoadData()
        {
            TfSQL tf = new TfSQL();
            string sqlExport = "select row_number() over(order by a90_datetime desc) stt, a90_model Model, a90_line line, a90_barcode Barcode, a90_status status, a90_datetime DateTime from t_checkpusha90main where a90_datetime > '" + dtpFrom.Value.ToString() + "' order by a90_datetime desc";
            DataTable dt = new DataTable();

            tf.sqlDataAdapterFillDatatable(sqlExport, ref dt);
            dgvData.DataSource = dt;
            dgvData.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dgvData.Columns["stt"].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;

            if (dgvData.RowCount > 0)
            {
                for (int i = 0; i < dgvData.RowCount; i++)
                {
                    if (dgvData.Rows[i].Cells["status"].Value.ToString() == "NG")
                    {
                        dgvData.Rows[i].Cells["status"].Style.BackColor = Color.Red;
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
            if (chk.Checked)
            {
                Pass pa = new Pass(this);
                pa.ShowDialog();
                if (login == true)
                {
                    chk.Checked = true;
                }
                else chk.Checked = false;
            }
            else login = false;
        }

        private void cmbModel_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void cmbLine_SelectedIndexChanged(object sender, EventArgs e)
        {
            LoadInfo();
        }
        public void LoadInfo()
        {
            if (!Directory.Exists(@"C:\A90")) { Directory.CreateDirectory(@"C:\A90"); }
            if (!File.Exists(@"C:\A90\info.csv")) { File.Create(@"C:\A90\info.csv"); }
            var reader = new StreamReader(@"C:\A90\info.csv");
            var s = reader.ReadLine();
            string[] va = s.Split(',').ToArray();
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
            //if (login)
            //{
            if (txtBarcodeNoise.Text.Trim() != "")
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
                TfSQL tf = new TfSQL();
                string sqlUpdate = "update t_checkpusha90main set a90_noise_status = '" + status + "' where a90_barcode = '" + txtBarcodeNoise.Text + "'";
                if (tf.sqlExecuteNonQuery(sqlUpdate, false))
                {
                    //LoadDGV(dgv, txt_barcode.Text, true);
                    txtBarcodeNoise.Text = null;
                    txtBarcodeNoise.SelectNextControl(txtBarcodeNoise, true, false, true, true);
                    timerNoise.Interval = int.Parse(txtTimerNoise.Text) * 1000;
                    timerNoise.Enabled = true;
                }
                else dgvNoise.DataSource = null;
            }
            else return;
            //}
        }
        private void tabNoise_MouseClick(object sender, MouseEventArgs e)
        {
            UpdateStatusNoise(e);
        }
    }
}
