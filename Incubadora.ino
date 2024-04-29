#include <LiquidCrystal.h>
LiquidCrystal LCD(1,2,4,5,6,7);
int foco = 13;
int ventilador = 10;
int botton1 = 8;
int botton2 = 9;
int maximo = 27;
int estado = 1;
int cantidad1=0, cantidad2=0;
int mmin = 18; 
int sensor;
char grados = 223;
float temperatura;

void setup() {
  LCD.begin(16,2);
  pinMode(botton1,INPUT);
  pinMode(botton2,INPUT);
  pinMode(foco,OUTPUT);
  pinMode(ventilador,OUTPUT);
  LCD.setCursor(0,0);
  LCD.print("Encubadora");
}

void escaneo()
{
  sensor = analogRead(A0);
  temperatura=((sensor*5000.0)/1023)/10;
}
void cambioestado()
{
  if(digitalRead(botton1) == LOW)
  {
    cantidad1=cantidad1+1;
    if(cantidad1 == 1)
    {
      maximo=30;
    }
    if(cantidad1 == 2)
    {
      maximo=27;
      cantidad1=0;
    }
  LCD.setCursor(0,0);
  LCD.print("cambio de maximo");
  LCD.setCursor(0,1);
  LCD.print(maximo); LCD.print(" C"); LCD.print(grados);
  delay(1000);
  LCD.clear();
  }
  if(digitalRead(botton2) == LOW)
  {
     cantidad2=cantidad2 + 1;
     if(cantidad2 == 1)
    {
      mmin = 20;
    }
    if(cantidad2 == 2)
    {
      mmin = 18;
      cantidad2 = 0;
    }
    LCD.setCursor(0,0);
    LCD.print("cambio de minimo");
    LCD.setCursor(0,1);
    LCD.print(mmin); LCD.print(" C"); LCD.print(grados);
    delay(1000);
    LCD.clear();
  }
  LCD.setCursor(0,0);
  LCD.print("Encubadora");
}
void loop() 
{
  LCD.setCursor(0,1);
  LCD.print(temperatura,1); LCD.print(" C"); LCD.print(grados);
  escaneo();
  cambioestado();
  if(temperatura>maximo)
  {
    estado=1;
  }
  if(temperatura<mmin)
  {
    estado=2;
  }
  if(estado==1)
  {
    digitalWrite(foco,LOW);
    digitalWrite(ventilador,HIGH);
  }
  if(estado==2)
  {
    digitalWrite(foco,HIGH);
    digitalWrite(ventilador,LOW);
  }
}