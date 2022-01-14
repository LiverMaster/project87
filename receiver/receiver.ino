#include <ESP8266WiFi.h>
#include <PubSubClient.h>

String temp_str;
char cnt[5];

const char* ssid     = "Yuugure";
const char* password = "Hatsuharu";
const char *mqtt_broker = "192.168.0.160";
const char *topic = "sys";
const char *mqtt_username = "receiver";
const char *mqtt_password = "NULL";
const int mqtt_port = 1883;

int status = WL_IDLE_STATUS;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() 
{
  Serial.begin(9600);
  InitWiFi();
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  
  while (!client.connected()) 
      reconnect();
   
  if(client.connected())
    {
      Serial.print("MQTT connected to ");
      Serial.print(mqtt_broker);
      Serial.print(":1883\n\n");
    }
    
  client.subscribe(topic); //訂閱MQTT頻道
  client.publish(topic, "receiver first connect");
}

void loop() 
{  
  status = WiFi.status(); //檢測wifi連線
  if ( status != WL_CONNECTED)
  {
    while ( status != WL_CONNECTED)
    {
      Serial.println("reconnecting to WiFi...");
      status = WiFi.begin(ssid, password);
      delay(3000);
    }
    Serial.println("reconnected");
  }
  
  client.loop();
}


void InitWiFi() //wifi連線
{
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi connected");
  Serial.print("(");
  Serial.print(ssid);
  Serial.println(")");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println("\n");
  delay(1000);
}


void reconnect() //MQTT連線
{
    Serial.println("Connecting to MQTT Server ...");
    
    String client_id = "receiver";
    Serial.printf("Client %s", client_id.c_str());
    Serial.printf("(%s) is trying to connect to MQTT broker\n", String(WiFi.macAddress()).c_str());
    
    
    if ( client.connect(client_id.c_str(), mqtt_username, mqtt_password) ) 
    {
      Serial.println( "..." );
    } 
    
    else 
    {
      Serial.print( "[FAILED] MQTT connect error code = " );
      Serial.print( client.state() );
      Serial.println("");
      delay( 5000 );
    }
  
}


void callback(char *topic, byte *payload, unsigned int length) //顯示訂閱頻道訊息
{
    String messageTemp;

    Serial.print("from MQTT: ");   
    for (int i = 0; i < length; i++) 
    {   
        Serial.print((char) payload[i]);
        if(isDigit(payload[i]))
          messageTemp += (char)payload[i];
    }
    Serial.println("\n");

    if (messageTemp!=0)
    {
      Serial.print("from serial: ");
      Serial.print(messageTemp);
      Serial.println("\n");
    }
}
