//#include <DHT.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

char ssid[] = "TaoLaGa49";                 // Network Name
char pass[] = "longcoi123";                 // Network Password

WiFiServer server(80);
WiFiClient client;
MySQL_Connection conn((Client *)&client);

char INSERT_SQL[] = "INSERT INTO iottechn_smarthome.m_userlogin(userlogin_id, userlogin_name, userlogin_pass, userlogin_permission, userlogin_section, userlogin_datetime) VALUES (1,'long','long','admin','FA',now())";
//char INSERT_SQL[] ="INSERT INTO `iottechn_smarthome.m_userlogin`(`userlogin_id`, `userlogin_name`, `userlogin_pass`, `userlogin_permission`, `userlogin_section`, `userlogin_datetime`) VALUES (1,'long','long','admin','FA',now())";

char query[128];
//112.213.89.26 112.213.89.26
IPAddress server_addr(112, 213 ,89, 26);          // MySQL server IP
//char hostname[] = "mysql06.dotvndns.vn";
//char databasename = "iottechn_smarthome";
char user[] = "iottechn_admin";           // MySQL user
char password[] = "admin1@";       // MySQL password

void setup() {

  Serial.begin(9600);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");


  Serial.print("Assigned IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  Serial.println("Connecting to database");

  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(200);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("Connected to SQL Server!");

}

void loop() {
  delay(10000); //10 sec

  sprintf(query, INSERT_SQL);
  Serial.println("Recording data.");
  Serial.println(query);

  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

  cur_mem->execute(query);

  delete cur_mem;

}
