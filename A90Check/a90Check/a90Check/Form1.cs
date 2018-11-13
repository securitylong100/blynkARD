using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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
            AcceptButton = btn_check;
            if (txt_barcode.Text !=null)
            {


            }
        }
        private void btn_check_Click(object sender, EventArgs e)
        {
            if (txt_barcode2.Text != "")
            {
                LoadDGV(txt_barcode2.Text, false);
                TfSQL con = new TfSQL();
                string sql = "select a90_status from t_checkpusha90 where  a90_barcode = '" + txt_barcode2.Text + "' order by a90_id desc limit 1";
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
        
        public void LoadDGV(string barcode, bool order)
        {
            TfSQL tf = new TfSQL();
            DataTable dt = new DataTable();
            string sqlDGV = "select a90_barcode, a90_status, a90_datetime from t_checkpusha90 where a90_barcode = '" + barcode + "' ";

            if (order) { sqlDGV += "order by a90_datetime desc limit 1"; }
            else { sqlDGV += "order by a90_datetime desc"; }
            
            tf.sqlDataAdapterFillDatatable(sqlDGV, ref dt);
            dgv.DataSource = dt;

            if (dgv.RowCount > 0)
            {
                dgv.Columns["a90_barcode"].HeaderText = "Barcode";
                dgv.Columns["a90_status"].HeaderText = "Status";
                dgv.Columns["a90_datetime"].HeaderText = "DateTime";
            }
            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
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
                string sqlInsert = "insert into t_checkpusha90(a90_barcode, a90_status, a90_datetime ,a90_factory) ";
                sqlInsert += "values('" + txt_barcode.Text + "','" + status + "', now(),'NCVP')";
                if (tf.sqlExecuteNonQuery(sqlInsert, false))
                {
                    LoadDGV(txt_barcode.Text, true);
                    txt_barcode.Text = null;
                    txt_barcode.SelectNextControl(txt_barcode, true, false, true, true);
                    timer1.Interval = int.Parse(txtTimer.Text)*1000;
                    timer1.Enabled = true;
                }
                else dgv.DataSource = null;
            }
            else return;
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
            TfSQL tf = new TfSQL();
            string sqlExport = "select a90_barcode Barcode, a90_status status, a90_datetime DateTime from t_checkpusha90 where a90_datetime > '" + dtpFrom.Value.ToString() + "' and a90_datetime < '" + dtpTo.Value.ToString() + "' order by a90_datetime desc";
            DataTable dt = new DataTable();

            tf.sqlDataAdapterFillDatatable(sqlExport, ref dt);

            ExcelClass ex = new ExcelClass();
            ex.ExportToExcel(dt);
        }

        private void txtTimer_KeyPress(object sender, KeyPressEventArgs e)
        {
            
        }

        private void btnView_Click(object sender, EventArgs e)
        {
            TfSQL tf = new TfSQL();
            string sqlExport = "select a90_barcode Barcode, a90_status status, a90_datetime DateTime from t_checkpusha90 where a90_datetime > '" + dtpFrom.Value.ToString() + "' and a90_datetime < '" + dtpTo.Value.ToString() + "' order by a90_datetime desc";
            DataTable dt = new DataTable();

            tf.sqlDataAdapterFillDatatable(sqlExport, ref dt);
            dgv.DataSource = dt;

        }
    }
}
