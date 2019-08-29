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
    public class ConnectionDataTableSql
    {
        public static DataTable callsql(string sql)
        {
            DataTable dt = new DataTable();
            try
            {
                NpgsqlConnection cn;
                cn = ConnectionServer.CreateConnection();
                //NpgsqlDataAdapter da;
                //da = new NpgsqlDataAdapter(sql, cn);
                NpgsqlCommand cmd = new NpgsqlCommand(sql, cn);
                NpgsqlDataReader reader = cmd.ExecuteReader();
                //da.Fill(dt);
                dt.Load(reader);
                cn.Close();
                return dt;
            }
            catch (Exception ex)
            {
                MessageBox.Show("SQL executeschalar moethod failed." + System.Environment.NewLine + ex.Message
                                , "Database Responce", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                ConnectionServer.CreateConnection().Close();
                return dt;
            }
        }
    }
}
