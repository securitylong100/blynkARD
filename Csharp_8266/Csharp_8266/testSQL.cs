using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Csharp_8266
{
    public partial class testSQL : Form
    {        
        public static string sernodb = "laa10_003201908";
        public static string inspectdb = sernodb + "data";
        DateTime datea;
        string datef;
        string datet;
        int c;
        public DataTable ds;
        List<string> list = new List<string>();

        public testSQL()
        {
            InitializeComponent();
            ModelList();
            ds = new DataTable();
        }

        /// <summary>
        /// Get model list
        /// </summary>
        void ModelList()
        {
            DataTable dt = ConnectionDataTableSql.callsql("select distinct model from procinsplink");
            for (int i = 0; i < dt.Rows.Count; i++)
            {
                cmbModel.Items.Add(dt.Rows[i]["model"]);
            }
        }

        /// <summary>
        /// Get treeview
        /// </summary>
        /// <param name="model"></param>
        void GetTreeview(string model)
        {
            if(model != "")
            {
                TreeNode root = new TreeNode(model);
                trInspect.Nodes.Add(root);
                DataTable dt = ConnectionDataTableSql.callsql("select distinct inspect from procinsplink"
                    + " where model = '" + model + "'");
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    root.Nodes.Add(dt.Rows[i]["inspect"].ToString());
                }
            }
        }

        private void trInspect_AfterCheck(object sender, TreeViewEventArgs e)
        {
            setchecknode(e.Node, e.Node.Checked);
        }

        private void setchecknode(TreeNode node, bool check)
        {
            foreach(TreeNode child in node.Nodes)
            {
                if(child.Checked != check) child.Checked = check;                
                if(child.Nodes.Count > 0) setchecknode(child, check);
            }
        }

        /// <summary>
        /// Take treeview into list
        /// </summary>

        private void selectnode(TreeNodeCollection root)
        {
            foreach(TreeNode child in root)
            {
                if (child.Checked == true)
                    list.Add(child.Text);
                selectnode(child.Nodes);
            }
            if (root.ToString() == cmbModel.Text) list.RemoveAt(0);
        }

        /// <summary>
        /// Create string inspect and multxt for search data
        /// </summary>
        /// <returns></returns>
        /// 
        private string inspects()
        {
            try
            {
                list.RemoveAt(0);
                string sum = "'" + list[0] + "'";
                foreach (string str in list)
                {
                    sum += ",'" + str + "'";
                }
                return sum;
            }
            catch(Exception) { return "''"; }
        }

        private string multxt()
        {
            try
            {
                string l = "'" + txtBarcode.Lines[0] + "'";
                for (int i = 1; i < txtBarcode.Lines.Length; i++)
                    l += ",'" + txtBarcode.Lines[i] + "'";
                return l;
            }
            catch(Exception) { return "''"; }
        }

        public void gettable()
        {
            string serno = multxt();
            string inspect = inspects();
            DataTable dts = new DataTable();
            DataTable dti = new DataTable();
            
            string cmd;
            string cmd2;
            if (serno != "''")
            {
                cmd = "select serno, lot, model, site, factory, line, process, inspectdate from " + sernodb + " where serno in(" + serno + ") ";
                cmd2 = "select serno, inspectdate, inspect, inspectdata from " + inspectdb + " where serno in(" + serno + ") and inspect in(" + inspect + ")";
            }
            else if (serno == "''" && datef != "" && datet != "")
            {
                cmd = "select serno, lot, model, site, factory, line, process, inspectdate from " + sernodb + " where inspectdate > '" + datef + "' and inspectdate < '" + datet + "'";
                cmd2 = "select serno, inspectdate, inspect, inspectdata from " + inspectdb + " where inspect in(" + inspect + ") and inspectdate > '" + datef + "' and inspectdate < '" + datet + "'";

            }
            else
            {
                cmd = "select serno, lot, model, site, factory, line, process, inspectdate from " + sernodb;
                cmd2 = "select serno, inspectdate, inspect, inspectdata from " + inspectdb + " where inspect in(" + inspect + ")";
            }
            dts = ConnectionDataTableSql.callsql(cmd);
            dti = ConnectionDataTableSql.callsql(cmd2);

            DataTable view = dti.DefaultView.ToTable(true, "inspect");
            for (int i = 0; i < view.Rows.Count; i++)
            {
                dts.Columns.Add(view.Rows[i]["inspect"].ToString());
            }
            //string filename = "data";
            //string path = filename + ".csv";
            //if (File.Exists(path))
            //{
            //    filename = filename + 1;
            //    path = filename + "csv";
            //}
            //using (StreamWriter sw = new StreamWriter(path, false, Encoding.UTF8))
            {
                for (int row = 0; row < dts.Rows.Count; row++)
                {
                    for (int irow = 0; irow < dti.Rows.Count; irow++)
                    {
                        if (dts.Rows[row]["serno"].ToString() == dti.Rows[irow]["serno"].ToString())
                        {
                            for (int col = 0; col < dts.Columns.Count; col++)
                            {
                                if (dts.Columns[col].ToString() == dti.Rows[irow]["inspect"].ToString())
                                {
                                    dts.Rows[row][col] = dti.Rows[irow]["inspectdata"].ToString();
                                    //sw.WriteLine(dts.Rows[row]);
                                    //sw.Flush();
                                }
                            }
                        }
                    }
                }
                //sw.Close();
            }
            ds = dts;
        }

        private void cmbModel_TextChanged(object sender, EventArgs e)
        {
            trInspect.Nodes.Clear();
            string model = cmbModel.Text;
            datea = dtDatef.Value;
            sernodb = model + datea.Year.ToString("0000") + datea.Month.ToString("00");
            inspectdb = sernodb + "data";
            GetTreeview(model);
        }

        private void btnSearch_Click(object sender, EventArgs e)
        {
            try
            {
                c = 0;
                ds.Clear();
                dgvdt.Refresh();
                datef = dtDatef.Text + " " + cmbHoursf.Text + ":" + cmbMinf.Text + ":00";
                datet = dtDatet.Text + " " + cmbHourst.Text + ":" + cmbMint.Text + ":00";
                selectnode(trInspect.Nodes);
                timer1.Enabled = true;
                Thread tab = new Thread(gettable);
                tab.Start();
                tab.IsBackground = true;
                if (tab.IsBackground)
                    tsProcessing.Text = "processing...";
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "NoInspect", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            c++;
            tsTime.Text = (c / 100).ToString() + "," + ((c % 100) / 10).ToString() + " s";
            if (ds.Rows.Count != 0)
            {
                dgvdt.DataSource = ds;
                tsProcessing.Text = dgvdt.Rows.Count.ToString() + " Rows";
                timer1.Enabled = false;
            }
        }

        private void createCSV()
        {
            string filename = "data";
            string path = filename + ".csv";
            if (File.Exists(path))
            {
                filename = filename + 1;
                path = filename + ".csv";
            }
            StreamWriter sw = new StreamWriter(path, true);
            for(int i = 0; i < ds.Rows.Count; i++)
            {
                sw.Write(ds.Rows[i].ToString());
            }
            sw.Flush();
            sw.Close();
        }

        private void btnCSV_Click(object sender, EventArgs e)
        {
            try
            {
                c = 0;
                ds.Clear();
                datef = dtDatef.Text + " " + cmbHoursf.Text + ":" + cmbMinf.Text + ":00";
                datet = dtDatet.Text + " " + cmbHourst.Text + ":" + cmbMint.Text + ":00";
                selectnode(trInspect.Nodes);
                timer2.Enabled = true;
                Thread tab = new Thread(gettable);
                tab.Start();
                tab.IsBackground = true;
                if (tab.IsBackground)
                    tsProcessing.Text = "processing...";
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "NoInspect", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            c++;
            tsTime.Text = (c / 100).ToString() + "," + ((c % 100) / 10).ToString() + " s";
            if (ds.Rows.Count != 0)
            {
                createCSV();
                tsProcessing.Text = ds.Rows.Count + " Rows";
                timer2.Enabled = false;
            }
        }
    }
}
