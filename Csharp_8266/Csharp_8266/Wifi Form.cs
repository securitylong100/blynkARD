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

namespace Csharp_8266
{
    public partial class Wifi_Form : Form
    {
        int c;
        public DataTable ds;
        public Wifi_Form()
        {
            InitializeComponent();
        }

        public void gettable()
        {
            DataTable dts = new DataTable();
            DataTable dti = new DataTable();
            string cmd = "select serno, lot, model, site, factory, line, process, inspectdate from laa10_003201908 where serno like 'K820%' and inspectdate > '2019-08-20 06:00' and inspectdate < '2019-08-20 12:00'";
            dts = ConnectionDataTableSql.callsql(cmd);
            string cmd2 = "select serno, inspectdate, inspect, inspectdata from laa10_003201908data where serno like 'K820%' and inspectdate > '2019-08-20 06:00' and inspectdate < '2019-08-20 12:00'";
            dti = ConnectionDataTableSql.callsql(cmd2);

            DataTable view = dti.DefaultView.ToTable(true, "inspect");
            for (int i = 0; i < view.Rows.Count; i++)
            {
                dts.Columns.Add(view.Rows[i]["inspect"].ToString());
            }
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
                            }
                        }
                    }
                }
            }
            ds = dts;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            c = 0;
            ds = new DataTable();
            dgvData.Rows.Clear();
            dgvData.Refresh();
            timer1.Enabled = true;
            Thread tab = new Thread(gettable);
            tab.Start();
            tab.IsBackground = true;
            if (tab.IsBackground)
                lbProcessing.Text = "processing...";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            c++;
            lbTimer.Text = (c / 100).ToString() + "," + ((c % 100) / 10).ToString() + " s";
            if (ds.Rows.Count != 0)
            {
                dgvData.DataSource = ds;
                timer1.Enabled = false;
            }
        }

        private void Wifi_Form_Load(object sender, EventArgs e)
        {

        }
    }
}