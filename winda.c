#define czyRaport 1
#define lag 0

//Przylacza Arduino
int Button1Pin =A0;//numer pinu dla "Przycisk zadanie 0-go piÄ?tra"
int Button2Pin =A2;//numer pinu dla "Przycisk zadanie 2-go piÄ?tra"
int Button3Pin =A3;//numer pinu dla "Przycisk zadanie 3-go piÄ?tra"
int Sensor1Pin =A4;//numer pinu dla "Sensor obecnosci kabiny na 0-szym pietrze"
int Sensor2Pin =12;//numer pinu dla "Sensor obecnosci kabiny na 2-gim pietrze"
int Sensor3Pin =13;//numer pinu dla "Sensor obecnosci kabiny na 3-im pietrze"
int Relay4Pin=4;//numer pinu dla Control Signal of Relay 4 / Output Signal Q2 / Start/Stop      Signal
int Relay3Pin=5;//numer pinu dla Control Signal of Relay 3 / Output Signal Q1 / Forward/Reverse Signal
//Zmienne globalne
boolean Q1 = 0;//Forward/Reverse Control Signal Relay 3
boolean Q2 = 0;//Start/Stop Control Signal Relay 4
boolean I1 = 0;//Odczyt z "Przycisk zadanie 0-go poziomu"
boolean I3 = 0;//Odczyt z "Przycisk zadanie 2-go poziomu"
boolean I4 = 0;//Odczyt z "Przycisk zadanie 3-go poziomu"
boolean I5 = 0;//Odczyt z "Sensor obecnosci kabiny na 0. poziomie"
boolean I7 = 0;//Odczyt z "Sensor obecnosci kabiny na 2. poziomie"
boolean I8 = 0;//Odczyt z "Sensor obecnosci kabiny na 3. poziomie"

boolean M1 = 0;//Flaga stanu
boolean M2 = 0;//Flaga stanu
boolean M3 = 0;//Flaga stanu
boolean M4 = 0;//Flaga stanu
boolean M5 = 0;//Flaga stanu
boolean M6 = 1;//Flaga stanu
boolean M7 = 0;//Flaga stanu
boolean M9 = 0;//Flaga stanu
boolean M10 = 0;//Flaga stanu
//...................................................................

void raport()
{
  Serial.println("Odczyt przyciskow  ");
  Serial.print(I1);
  Serial.print(I3);
  Serial.print(I4);
  Serial.println();
  Serial.println("Odczyt sensorow  ");
  Serial.print(I5);
  Serial.print(I7);
  Serial.print(I8);
  Serial.println();  
}

void odczytWejsc()
{
  I1 = digitalRead(Button1Pin);
  I3 = digitalRead(Button2Pin);
  I4 = digitalRead(Button3Pin);
  I5 = digitalRead(Sensor1Pin);
  I7 = digitalRead(Sensor2Pin);
  I8 = digitalRead(Sensor3Pin);
}

void funkcjaPrzejscia()
{
  //Obliczana nowa wartosci flagi
  boolean M1prim = 0;
  boolean M2prim = 0;
  boolean M3prim = 0;
  boolean M4prim = 0;
  boolean M5prim = 0;
  boolean M6prim = 0;
  boolean M7prim = 0;
  boolean M9prim = 0;
  boolean M10prim = 0;
 //...............................  
  //Obliczenie wartosci funkcji przejsc stanow (flag)
  M1prim = M1&!I3&!I4 | M9&I5 | M10&I5;
  M2prim = M2&!I1&!I4 | M4&I7 | M7&I7;
  M3prim = M3&!I1&!I3 | M5&I8 | M6&I8;
  M4prim = M1&I3&!I4 | M4&!I7;
  M5prim = M2&!I1&I4 | M5&!I8;
  M6prim = M1&!I3&I4 | M6&!I8;
  M7prim = M3&!I1&I3 | M7&!I7;
  M9prim = M3&I1&!I3 | M9&!I5;
  M10prim = M2&I1&!I4 | M10&!I5;
//  ............................  
  //Przepisanie "nowych" wartosci do "starych" 
  M1 = M1prim;
  M2 = M2prim; 
  M3 = M3prim; 
  M4 = M4prim; 
  M5 = M5prim; 
  M6 = M6prim; 
  M7 = M7prim; 
  M9 = M9prim; 
  M10 = M10prim;  
}

void funkcjaWyjscia() 
{
  Q1 = M1 | M2 | M3;
  Q2 = M7 | M9 | M10; 
}
  
void zapisWyjscia()
{
  digitalWrite(Relay3Pin,Q1);
  digitalWrite(Relay4Pin,Q2);
}

void setup() 
{
  pinMode(Button1Pin, INPUT);
  pinMode(Button2Pin, INPUT);
  pinMode(Button3Pin, INPUT);
  pinMode(Sensor1Pin, INPUT);
  pinMode(Sensor2Pin, INPUT);
  pinMode(Sensor3Pin, INPUT);
  pinMode(Relay3Pin, OUTPUT);
  pinMode(Relay4Pin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Koniec wykonywania Setup");
 }

void loop() 
{  
  odczytWejsc();  
  funkcjaPrzejscia();
  funkcjaWyjscia();
  zapisWyjscia();
  raport();
}

