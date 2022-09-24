#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
//int pinStateCurrent   = LOW;  // current state of pin
//int pinStatePrevious  = LOW;  // previous state of pin
const char* ssid = "shyam"; 
const char* password = "123456789";

const char *host = "maker.ifttt.com";
const char *privateKey = "cUh3bapHr2Q61af3cb8TjGOdC407Aw-v2bAKSSySCNm";
void send_event(const char *event);

WebServer server(80); 
void send_event(const char *event);

 int buzzer = 5; //buzzer 
 int sensor_pin = 2; //pir sensor
 const int trigPin = 13;
 const int echoPin = 14;
 const int ledPin = 23;

 long duration;
int distance;
int safetyDistance;
  
String Message;
String Message1;


const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>

<head>
  <title>IOT BASED SECURITY SYSTEM</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <h1 style="text-align:center; color:blue;font-size: 2.5rem;"><img src="https://ibb.co/8DVyRg5"  width="100" height="100"><img src="https://ibb.co/8DVyRg5"  width="100" height="100"></h1>
  <h1 style="text-align:center; color:rgb(128, 255, 0);font-size: 3rem;">PIET AICTE IDEA LAB</h1>
  <h1 style="text-align:center; color:blue;font-size: 2.5rem;">IOT BASED SECURITY SYSTEM</h1>
  <h1 style="text-align:center; color:rgb(255, 0, 200);font-size: 2.15rem;">GROUP 7 </h1>
  <h1 style="text-align:center; color:black;font-size: 2rem;">SHOAIB ALI</h1>
  <h1 style="text-align:center; color:black;font-size: 2rem;">SHYAM SINGH</h1>
  <h1 style="text-align:center; color:black;font-size: 2rem;">GIGNESH</h1>
  <h1 style="text-align:center; color:black;font-size: 2rem;">SHASHANK SINGH SHEKHAWAT</h1>
  <style>
    canvas {
      -moz-user-select: none;
      -webkit-user-select: none;
      -ms-user-select: none;
    }

    #data_table {
      font-family: New Times Roman;
      border-collapse: collapse;
      width: 100%;
      text-align: center;
      font-size: 0.8rem;
    }

    #data_table td,
    #data_table th {
      border: 3px solid #ddd;
      padding: 15px;
    }

    #data_table tr:nth-child(even) {
      background-color: #206283;
    }

    #data_table tr:hover {
      background-color: #e3dada;
    }

    #data_table th {
      padding-top: 20px;
      padding-bottom: 20px;
      text-align: center;
      background-color: #ff000400;
      color: rgb(3, 10, 9);
    }
  </style>
</head>

<body>
  
  <a href="https://www.google.co.in" target="_blank">Go to google</a><br>
  <a href="https://www.facebook.com" target="_blank">Go to facebook</a><br>
  <a href="https://www.youtube.com" target="_blank">Go to youtube</a><br>
  <a href="https://www.linkedin.com" target="_blank">Go to linkedin</a><br>
  <a href="https://collegedunia.com/college/14576-poornima-institute-of-engineering-and-technology-piet-jaipur" target="_blank">Go to PIET</a><br>
    <div>
    <table id="data_table">
      <tr>
        <th>Time</th>
        <th>Activity</th>
      
      </tr>
    </table>
  </div>
  <br>
  <br>
  <script>

var Avalues = [];
var dateStamp = [];

setInterval(function() {
  getData();
}, 3000); 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
  var date = new Date();
  var txt = this.responseText;
  var obj = JSON.parse(txt); 
      Avalues.push(obj.Activity);
      dateStamp.push(date);

    var table = document.getElementById("data_table");
    var row = table.insertRow(1); 
    var cell1 = row.insertCell(0);
    var cell2 = row.insertCell(1);
    cell1.innerHTML = date;
    cell2.innerHTML = obj.Activity;
    }
  };
  xhttp.open("GET", "read_data", true); 
  xhttp.send();
}    
</script>
</body>
</html>

)====="; 
void handleRoot() {
 String s = MAIN_page; 
 server.send(200, "text/html", s); 
}
void read_data() {
  int state = digitalRead(sensor_pin); 
  delay(500);                        
  //Serial.print(state);
    if(state == HIGH){ 
    digitalWrite(ledPin,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(1000);
    digitalWrite(ledPin,LOW);
    digitalWrite(buzzer,LOW);
    delay(1000);
     Message = "Theft Detected";
    String data = "{\"Activity\":\""+ String(Message) +"\"}";
    server.send(200, "text/plane", data); 
    send_event("Theft_Detection");               
    Serial.println("Theft detected!");
    
    }
}
void setup() {
 Serial.begin(115200);
 
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print("Connecting...");
 }
 Serial.println("");
 Serial.println("Successfully connected to WiFi.");
 Serial.println("IP address is : ");
 Serial.println(WiFi.localIP());
 
 server.on("/", handleRoot);     
 server.on("/read_data", read_data);
 server.begin();               
 
 pinMode(sensor_pin, INPUT); 
 pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT); 
//digitalWrite (buzzer, LOW);

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
// pinMode(buzzer, OUTPUT);
//  pinMode(ledPin, OUTPUT); 
 

// Prints the distance on the Serial Monitor

}
void loop(){
  server.handleClient();
  Serial.begin(115200);
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

safetyDistance = distance;
//Serial.print("cm ");

if (safetyDistance <= 5 && safetyDistance >0)
{
  digitalWrite(buzzer, HIGH); 
   digitalWrite(ledPin, HIGH);
   delay(300);
   digitalWrite(buzzer, LOW);
   digitalWrite(ledPin, LOW);
    delay(300);
    digitalWrite(buzzer, HIGH); 
   digitalWrite(ledPin, HIGH);
    delay(300);
   digitalWrite(buzzer, LOW);
   digitalWrite(ledPin, LOW);
    delay(300);
    digitalWrite(buzzer, HIGH); 
   digitalWrite(ledPin, HIGH);
    delay(300);
    
}
else{
  digitalWrite(buzzer, LOW);
   digitalWrite(ledPin, LOW);
   delay(300);
}  
Serial.print("distance: ");
Serial.println(distance );       
}
void send_event(const char *event)
  {
  Serial.print("Connecting to "); 
  Serial.println(host); 
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  } 
  
  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += privateKey; 
  Serial.print("Requesting URL: ");
  Serial.println(url);  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  while(client.connected())
  {
    if(client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    } else {
      delay(50);
    };
  }  
  Serial.println();
  Serial.println("Closing Connection");
  client.stop();
  }
