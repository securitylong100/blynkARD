using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using Npgsql;
using System.Windows.Forms;


namespace Csharp_8266
{
    public class ConnectionStringSql
    {
        public string esql;
        public string callsql(string sql)
        {
            try
            {
                NpgsqlConnection cn;
                cn = ConnectionServer.CreateConnection();
                NpgsqlCommand command = new NpgsqlCommand(sql, cn);
                esql = Convert.ToString(command.ExecuteScalar());
                cn.Close();
                return esql;
            }
            catch (Exception ex)
            {
                MessageBox.Show("SQL executeschalar moethod failed." + System.Environment.NewLine + ex.Message
                                , "Database Responce", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                ConnectionServer.CreateConnection().Close();
                return esql;
            }
        }
    }
}
