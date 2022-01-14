#include <Servo.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

Servo tgt1;
bool vo;
int count;
bool hit;
bool hit_old;
String temp_str;
char cnt[5];

const char* ssid     = "Yuugure";
const char* password = "Hatsuharu";
const char *mqtt_broker = "192.168.0.160";
const char *topic = "sys";
const char *mqtt_username = "tgt1";
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
  client.publish(topic, "tgt1 first connect");

  initservo();
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
  
  vo=digitalRead(4);
  //Serial.println(vo);

  if(vo)
  {
    hit = 1;
    hit_old = hit;
  }
  else if(vo == 0)
    hit = 0;

  if(hit_old == 1 && hit == 0)
  {
    count++;
    Serial.print(" ");
    Serial.print(count);
    Serial.println(" hit ");
    delay(300);    
    hit_old = 0;
  }
  
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
    
    String client_id = "tgt1";
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
    
    Serial.print("topic:'");
    Serial.print(topic);
    Serial.print("'");
    Serial.println("message:");
    for (int i = 0; i < length; i++) 
    {
        messageTemp += (char)payload[i];
        Serial.print((char) payload[i]);
    }
    Serial.println("\n-----------------------");
    
    if(messageTemp == "down")
    {
      if(tgt1.read()>50)
      {
        for(int k=70; k>=0; k--)
        {
         tgt1.write(k);
          delay(20);
        }
      }
      
    }
    
    if(messageTemp == "up")
    {
      if(tgt1.read()<20)
      {
        for(int m=0; m<=70; m++)
        {
          tgt1.write(m);
          delay(20);
        }
      }
      
    }
    
    if(messageTemp == "report")
    { 
      temp_str = String(count);
      temp_str.toCharArray(cnt, temp_str.length() + 1);
      client.publish(topic, cnt);
    }
}

void initservo()
{
  pinMode(0,OUTPUT);
  pinMode(4,INPUT);

  digitalWrite(0,HIGH);
  count = 0;
  hit =0;
  hit_old = 0;

  tgt1.attach(5,500,2400);
  if(tgt1.read()!=0)
    tgt1.write(0);
  delay(500);
  Serial.println("\n\n tgt1 initialized");
  delay(1000);
}
