using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace a90Check
{
    public partial class Pass : Form
    {
        public Form1 f1;
        public Pass(Form1 f1_)
        {
            InitializeComponent();
            f1 = f1_;
        }

        private void btnSubmit_Click(object sender, EventArgs e)
        {
            if (txtPass.Text == "1111")
            {
                f1.login = true;
                this.Close();
            }
        }
    }
}
