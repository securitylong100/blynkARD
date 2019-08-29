using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data;
using Npgsql;

namespace Csharp_8266
{
    public class ConnectionServer
    {
        public static Npgsql.NpgsqlConnection CreateConnection()
        {
          
                string strConnection = @"Server=192.168.145.12; Port=5432; User Id=pqm; Password=dbuser; Database=pqmdb; CommandTimeout=100; Timeout=100;";
                Npgsql.NpgsqlConnection conn = new Npgsql.NpgsqlConnection(strConnection);
                conn.Open();
                return conn;
        }        
    }
}
