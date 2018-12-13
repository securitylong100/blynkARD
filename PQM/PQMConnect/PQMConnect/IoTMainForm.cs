using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PQMConnect
{
    public partial class IoT_Main_Form : Form
    {
        public IoT_Main_Form()
        {
            InitializeComponent();
        }
        void callModel()
        {

            TfSQL tfSql = new TfSQL();
            string sqlcallModel = "select distinct model from modeltbl order by model";
            tfSql.getComboBoxData(sqlcallModel, ref cmb_model);
        }
        void callLine()
        {
            TfSQL tfSql = new TfSQL();
            string sqlcallLine = "select distinct line from processtbl where model = '" + cmb_model.Text + "' order by line";
            tfSql.getComboBoxData(sqlcallLine, ref cmb_line);
        }
        void callProcessSymbol()
        {

            TfSQL tfSql = new TfSQL();
            string sqlcallProcess = "select distinct process from processtbl where model = '" + cmb_model.Text + "' and line ='" + cmb_line.Text + "' order by process";
            tfSql.getComboBoxData(sqlcallProcess, ref cmb_process_symbol);

        }
        void callItemSymbol()
        {
            TfSQL tfSql = new TfSQL();
            string sqlcallItem = "select distinct inspect from procinsplink where model = '" + cmb_model.Text + "' and line ='" + cmb_line.Text + "' and process ='" + cmb_process_symbol.Text + "' order by inspect";
            tfSql.getComboBoxData(sqlcallItem, ref cmb_item_symbol);

        }

        private void cmb_model_SelectedIndexChanged(object sender, EventArgs e)
        {
            callLine();
        }
        private void cmb_line_SelectedIndexChanged(object sender, EventArgs e)
        {
            callProcessSymbol();
        }
        private void cmb_process_symbol_SelectedIndexChanged(object sender, EventArgs e)
        {
            callItemSymbol();
            TfSQL tfSql = new TfSQL();
            string sqlcallProcessName = "select  procname from processtbl where model = '" + cmb_model.Text + "' and line ='" + cmb_line.Text + "' and process ='" + cmb_process_symbol.Text + "'";
            txt_process_name.Text = tfSql.sqlExecuteScalarString(sqlcallProcessName);
        }
        private void cmb_item_symbol_SelectedIndexChanged(object sender, EventArgs e)
        {
            TfSQL tfSql = new TfSQL();
            string sqlcallItemName = "select  inspectname from procinsplink where model = '" + cmb_model.Text + "' and line ='" + cmb_line.Text + "' and process ='" + cmb_process_symbol.Text + "' and inspect = '"+ cmb_item_symbol.Text+ "'";
            txt_item_name.Text = tfSql.sqlExecuteScalarString(sqlcallItemName);
        }
        private void IoT_Main_Form_Load(object sender, EventArgs e)
        {
            callModel();
        }


    }
}
