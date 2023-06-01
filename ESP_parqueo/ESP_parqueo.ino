//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <WebServer.h>
#include <HardwareSerial.h>

#define UART1_BAUDRATE 115200
#define UART1_TX_PIN 2
#define UART1_RX_PIN 4

#define UART2_BAUDRATE 115200
#define UART2_TX_PIN 17
#define UART2_RX_PIN 16

HardwareSerial SerialPort1(1);
HardwareSerial SerialPort2(2);


//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
const char* ssid = "iPhonedeAldo";  // Enter your SSID here
const char* password = "Jamondepavo03";  //Enter your Password here

const int segmentPins[] = {13, 14, 12, 5, 18, 19, 27, 26};

int currentDigit = 0;

// Números en código de segmento común
const byte digitPatterns[] = {
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111   // 9
};


char parqueo1;
char parqueo2;
char P1;
char P2;
char P3;
char P4;
char P5;
char P6;
char P7;
char P8;

int FlagP1;
int FlagP2;
int FlagP3;
int FlagP4;
int FlagP5;
int FlagP6;
int FlagP7;
int FlagP8;

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  SerialPort1.begin(UART1_BAUDRATE, SERIAL_8N1, UART1_RX_PIN, UART1_TX_PIN);
  SerialPort2.begin(UART2_BAUDRATE, SERIAL_8N1, UART2_RX_PIN, UART2_TX_PIN);
  // Inicializa la comunicación serial en el puerto UART1 y UART2 con las velocidades de baudios y pines especificados
  // SERIAL_8N1 indica 8 bits de datos, sin paridad y 1 bit de parada
  // Los pines especificados se utilizarán para la comunicación UART1 y UART2
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  Serial.begin(9600);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // Directamente desde e.g. 192.168.0.8
  
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);


}

//************************************************************************************************
// Loop principal
//************************************************************************************************
void loop() {
  if (SerialPort1.available()) {
    parqueo1 = SerialPort1.read();
    Serial.print("UART1: ");
    Serial.println(parqueo1);
  }

  if (SerialPort2.available()) {
    parqueo2 = SerialPort2.read();
    Serial.print("UART2: ");
    Serial.println(parqueo2);
  }

  if (parqueo1 == 'a'){
    P1 = 'a';
    if (FlagP1 == 0 && currentDigit < 8){
      currentDigit++;
      FlagP1 = 1;
    }
  }
  if (parqueo1 == 'b'){
    if (FlagP1 == 1 && currentDigit > 0){
      currentDigit--;
      FlagP1 = 0;
    }
    P1 = 'b';
  }
  if (parqueo1 == 'c'){
    if (FlagP2 == 0 && currentDigit < 8){
      currentDigit++;
      FlagP2 = 1;
    }
    P2 = 'c';
  }
  if (parqueo1 == 'd'){
    if (FlagP2 == 1 && currentDigit > 0){
      currentDigit--;
      FlagP2 = 0;
    }
    P2 = 'd';
  }
  if (parqueo1 == 'e'){
    if (FlagP3 == 0 && currentDigit < 8){
      currentDigit++;
      FlagP3 = 1;
    }
    P3 = 'e';
  }
  if (parqueo1 == 'f'){
    if (FlagP3 == 1 && currentDigit > 0){
      currentDigit--;
      FlagP3 = 0;
    }
    P3 = 'f';
  }
  if (parqueo1 == 'g'){
    if (FlagP4 == 0 && currentDigit < 8){
      currentDigit++;
      FlagP4 = 1;
    }
    P4 = 'g';
  }
  if (parqueo1 == 'h'){
    if (FlagP4 == 1 && currentDigit > 0){
      currentDigit--;
      FlagP4 = 0;
    }
    P4 = 'h';
  }

  if (parqueo2 == 'a'){
    if (FlagP5 == 0 && currentDigit < 8){
      currentDigit++;
      FlagP5 = 1;
    }
    P5 = 'a';
  }
  if (parqueo2 == 'b'){
    if (FlagP5 == 1 && currentDigit > 0){
      currentDigit--;
      FlagP5 = 0;
    }
    P5 = 'b';
  }
  if (parqueo2 == 'c'){
    if (FlagP6 == 0 && currentDigit < 8){
      currentDigit++;
      FlagP6 = 1;
    }
    P6 = 'c';
  }
  if (parqueo2 == 'd'){
    if (FlagP6 == 1 && currentDigit > 0){
      currentDigit--;
      FlagP6 = 0;
    }
    P6 = 'd';
  }
  if (parqueo2 == 'e'){
    if (FlagP7 == 0 && currentDigit < 8){
      currentDigit++;
      FlagP7 = 1;
    }
    P7 = 'e';
  }
  if (parqueo2 == 'f'){
    if (FlagP7 == 1 && currentDigit > 0){
      currentDigit--;
      FlagP7 = 0;
    }
    P7 = 'f';
  }
  if (parqueo2 == 'g'){
    if (FlagP8 == 0 && currentDigit < 8){
      currentDigit++;
      FlagP8 = 1;
    }
    P8 = 'g';
  }
  if (parqueo2 == 'h'){
    if (FlagP8 == 1 && currentDigit > 0){
      currentDigit--;
      FlagP8 = 0;
    }
    P8 = 'h';
  }
  
  displayNumber(currentDigit);
  server.handleClient();

}

//************************************************************************************************
// Handler de Inicio página
//************************************************************************************************
void handle_OnConnect() {
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML());
}

//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML() {
  String pag = "<!DOCTYPE html>\n";
  pag += "<html lang=en>\n";
  pag += "<head>\n";
  pag += "<script>";
  pag += "  function autoRefresh() {";
  pag += "    window.location = window.location.href;";
  pag += "  }";
  pag += "  setInterval(autoRefresh, 2000);";
  pag += "</script>";
  pag += "<title>Servidor de Control de Parqueos</title>\n";
  pag += "<meta charset=utf-8>\n";
  pag += "<meta name=viewport content=\"width=device-width, initial-scale=1\">\n";
  pag += "<link rel=stylesheet href=https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/css/bootstrap.min.css>\n";
  pag += "<script src=https://cdn.jsdelivr.net/npm/jquery@3.6.4/dist/jquery.slim.min.js></script>\n";
  pag += "<script src=https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js></script>\n";
  pag += "<script src=https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/js/bootstrap.bundle.min.js></script>\n";
  pag += "</head>\n";
  pag += "<body>\n";
  pag += "<div class=container>\n";
  pag += "<h1>‎</h1>\n";
  pag += "<h2>Parqueos &#128663</h2>\n";
  pag += "<h6>‎</h6>\n";
  pag += "<p>\n";
  pag += "</p>\n";
  pag += "<table class=\"table table-bordered\">\n";
  pag += "<thead>\n";
  pag += "<tr>\n";
  pag += "<th>Parqueo</th>\n";
  pag += "<th>Estado</th>\n";
  pag += "</tr>\n";
  pag += "</thead>\n";
  pag += "<tbody>\n";
  pag += "<tr>\n";

  if (P1 == 'a'){
  pag += "<tr class=table-success>\n";
  pag += "<td>Parqueo 1</td>\n";
  pag += "<td>Disponible &#9989</td>\n";
  pag += "</tr>\n";
  }

  if (P1 == 'b'){
  pag += "<tr class=table-danger>\n";
  pag += "<td>Parqueo 1</td>\n";
  pag += "<td>Ocupado &#9940</td>\n";
  pag += "</tr>\n";
  }

  if (P2 == 'c'){
  pag += "<tr class=table-success>\n";
  pag += "<td>Parqueo 2</td>\n";
  pag += "<td>Disponible &#9989</td>\n";
  pag += "</tr>\n";
  }

  if (P2 == 'd'){
  pag += "<tr class=table-danger>\n";
  pag += "<td>Parqueo 2</td>\n";
  pag += "<td>Ocupado &#9940</td>\n";
  pag += "</tr>\n";
  }

  if (P3 == 'e'){
  pag += "<tr class=table-success>\n";
  pag += "<td>Parqueo 3</td>\n";
  pag += "<td>Disponible &#9989</td>\n";
  pag += "</tr>\n";
  }

  if (P3 == 'f'){
  pag += "<tr class=table-danger>\n";
  pag += "<td>Parqueo 3</td>\n";
  pag += "<td>Ocupado &#9940</td>\n";
  pag += "</tr>\n";
  }

  if (P4 == 'g'){
  pag += "<tr class=table-success>\n";
  pag += "<td>Parqueo 4</td>\n";
  pag += "<td>Disponible &#9989</td>\n";
  pag += "</tr>\n";
  }

  if (P4 == 'h'){
  pag += "<tr class=table-danger>\n";
  pag += "<td>Parqueo 4</td>\n";
  pag += "<td>Ocupado &#9940</td>\n";
  pag += "</tr>\n";
  }

  if (P5 == 'a'){
  pag += "<tr class=table-success>\n";
  pag += "<td>Parqueo 5</td>\n";
  pag += "<td>Disponible &#9989</td>\n";
  pag += "</tr>\n";
  }

  if (P5 == 'b'){
  pag += "<tr class=table-danger>\n";
  pag += "<td>Parqueo 5</td>\n";
  pag += "<td>Ocupado &#9940</td>\n";
  pag += "</tr>\n";
  }

  if (P6 == 'c'){
  pag += "<tr class=table-success>\n";
  pag += "<td>Parqueo 6</td>\n";
  pag += "<td>Disponible &#9989</td>\n";
  pag += "</tr>\n";
  }

  if (P6 == 'd'){
  pag += "<tr class=table-danger>\n";
  pag += "<td>Parqueo 6</td>\n";
  pag += "<td>Ocupado &#9940</td>\n";
  pag += "</tr>\n";
  }

  if (P7 == 'e'){
  pag += "<tr class=table-success>\n";
  pag += "<td>Parqueo 7</td>\n";
  pag += "<td>Disponible &#9989</td>\n";
  pag += "</tr>\n";
  }

  if (P7 == 'f'){
  pag += "<tr class=table-danger>\n";
  pag += "<td>Parqueo 7</td>\n";
  pag += "<td>Ocupado &#9940</td>\n";
  pag += "</tr>\n";
  }

  if (P8 == 'g'){
  pag += "<tr class=table-success>\n";
  pag += "<td>Parqueo 8</td>\n";
  pag += "<td>Disponible &#9989</td>\n";
  pag += "</tr>\n";
  }

  if (P8 == 'h'){
  pag += "<tr class=table-danger>\n";
  pag += "<td>Parqueo 8</td>\n";
  pag += "<td>Ocupado &#9940</td>\n";
  pag += "</tr>\n";
  }

  pag += "</tbody>\n";
  pag += "</table>\n";
  pag += "</div>\n";
  pag += "</body>\n";
  pag += "</html>";
  return pag;
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

void displayNumber(int digit) {
  // Apagar todos los segmentos
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], LOW);
  }

  // Obtener el patrón de segmentos para el dígito
  byte pattern = digitPatterns[digit];

  // Encender los segmentos correspondientes según el patrón
  for (int i = 0; i < 8; i++) {
    bool segmentState = bitRead(pattern, i);
    digitalWrite(segmentPins[i], segmentState);
  }
}
