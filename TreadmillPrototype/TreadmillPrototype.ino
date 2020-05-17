#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <FreqCount.h>
#include <Wire.h>
#include <EEPROM.h>
#include "RTClib.h"


RTC_DS1307 rtc;
char frase[20]="aaaaaaaaa";
int peso=90;
uint8_t contador=0,seteo1=0,comenzar=0,aumentar=0,contador1=0,medir_peso=0,k,comparar=0;
bool a,b;
float vel,recorrido,calorias,count;
int j,i;
int ss,mm,hh;
String e_dia; 
struct datos
{
  uint8_t dia;
  uint8_t mes;
  uint16_t anio;
  float ti_lunes;
  float ti_martes;
  float ti_miercoles;
  float ti_jueves;
  float ti_viernes;
  float ti_sabado;
  float ti_domingo;
  float re_lunes;
  float re_martes;
  float re_miercoles;
  float re_jueves;
  float re_viernes;
  float re_sabado;
  float re_domingo;
};

datos leer;

#define rs 22
#define en 24
#define D4 29
#define D5 30
#define D6 31
#define D7 32

LiquidCrystal lcd(rs,en,D4,D5,D6,D7);
void setup() 
{
  Serial.begin(9600);
  int ad=0;
  EEPROM.get(ad,leer);
  Serial.println(leer.dia);
  Serial.println(leer.mes);
  Serial.println(leer.anio);
  Serial.println("Dia lunes");
  Serial.println("Tiempo:");
  Serial.println(leer.ti_lunes);
  Serial.println("Recorrido");
  Serial.println(leer.re_lunes);
  Serial.println("Dia martes");
  Serial.println("Tiempo:");
  Serial.println(leer.ti_martes);
  Serial.println("Recorrido");
  Serial.println(leer.re_martes);
  Serial.println("Dia miercoles");
  Serial.println("Tiempo:");
  Serial.println(leer.ti_miercoles);
  Serial.println("Recorrido");
  Serial.println(leer.re_miercoles);
  Serial.println("Dia jueves");
  Serial.println("Tiempo:");
  Serial.println(leer.ti_jueves);
  Serial.println("Recorrido");
  Serial.println(leer.re_jueves);
  Serial.println("Dia viernes");
  Serial.println("Tiempo:");
  Serial.println(leer.ti_viernes);
  Serial.println("Recorrido");
  Serial.println(leer.re_viernes);
  Serial.println("Dia sabado");
  Serial.println("Tiempo:");
  Serial.println(leer.ti_sabado);
  Serial.println("Recorrido");
  Serial.println(leer.re_sabado);
  Serial.println("Dia domingo");
  Serial.println("Tiempo:");
  Serial.println(leer.ti_domingo);
   Serial.println("Recorrido");
  Serial.println(leer.re_domingo);
  
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  lcd.begin(16,2);
  lcd.clear();
  FreqCount.begin(1000);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(segundo);

  TCCR3B=1;

  pinMode(19, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(19),Interrupcion,FALLING);
  pinMode(52,INPUT_PULLUP);
  pinMode(53,INPUT_PULLUP);
  a=digitalRead(52);
  b=digitalRead(53);
  
  lcd.setCursor(0,0);
  sprintf(frase,"***Bienvenido***");
  lcd.print(frase);
  lcd.setCursor(0,1);
  sprintf(frase,"***Entrenador***");
  lcd.print(frase);
  delay(3000);
  
}

void loop() 
{
         k=0;
         comparar=0;
         guardar();
  while(medir_peso==0)
  {
     lcd.clear();
     lcd.setCursor(0,0);
     sprintf(frase,"Ingrese su peso:");
     lcd.print(frase);
     lcd.setCursor(0,1);
     sprintf(frase,"%d kg",peso);
     lcd.print(frase);
     delay(200);
  }
    if(contador==1)
    {
    lcd.clear();
    lcd.setCursor(0,0);
    sprintf(frase,"Entrenamiento:");
    lcd.print(frase);
    lcd.setCursor(0,1);
    sprintf(frase,"Basico");
    lcd.print(frase);  
    }else if(contador==2)
    {
    lcd.clear();
    lcd.setCursor(0,0);
    sprintf(frase,"Entrenamiento:");
    lcd.print(frase);
    lcd.setCursor(0,1);
    sprintf(frase,"Medio");
    lcd.print(frase);
    }else if(contador==3)
    {
    lcd.clear();
    lcd.setCursor(0,0);
    sprintf(frase,"Entrenamiento:");
    lcd.print(frase);
    lcd.setCursor(0,1);
    sprintf(frase,"Fuerte");
    lcd.print(frase);
    }else
    {
    lcd.clear();
    lcd.setCursor(0,0);
    sprintf(frase,"Entrenamiento:");
    lcd.print(frase);
    lcd.setCursor(0,1);
    sprintf(frase,"Libre");
    lcd.print(frase);
    }
    delay(200);
    
  while(seteo1==1)
  {
    if(comenzar==0){
      ss=0;
      mm=0;
      hh=0;
    }
    rampa(0,17,100,1,1);
    printRutinaBasico(1,1);
    if (ss>20)
    { 
      comenzar=0;
      aumentar=1;
    }
    while(aumentar==1)
    {   
        if(seteo1==0)break;
        rampa(17,18,800,2,1);
        printRutinaBasico(1,1);
        if(ss>40)
        { 
          comenzar=0;
          aumentar=2;
        }
    }
    while(aumentar==2)
    {   
        if(seteo1==0)break;
        rampa(18,19,800,2,1);
        printRutinaBasico(1,1);
        if(mm>=1)
        {
         comenzar=0;
         vel = FreqCount.read()*2*3.1416/(21*0.104);
         recorrido=0.01*vel*0.105*(mm*60+ss);
         desaceleracion(19,15,1000,3,1);
         pinMode(2,OUTPUT);
         digitalWrite(2,LOW);
         guardar();
         aumentar=0;
         contador=0;
         comenzar=0;
         seteo1=0;
        }
    }
  }

  while(seteo1==2)
  {
     if(comenzar==0){
      ss=0;
      mm=0;
      hh=0;
    }
    rampa(0,17,100,1,2);
    printRutinaBasico(2,2);
    if (ss>20)
    { 
      comenzar=0;
      aumentar=1;
    }
    while(aumentar==1)
    {   
        if(seteo1==0)break;
        rampa(17,18,800,2,2);
        printRutinaBasico(2,2);
        if(ss>40)
        { 
          comenzar=0;
          aumentar=2;
        }
    }
    while(aumentar==2)
    {   
        if(seteo1==0)break;
        rampa(18,19,800,2,2);
        printRutinaBasico(2,2);
        if(mm>=1)
        {
          comenzar=0;
          aumentar=3;
        }
    }
    while(aumentar==3)
    {   
        if (seteo1==0)break;
        desaceleracion(19,18,800,4,2);
        printRutinaBasico(2,2);
        if(mm>=1 && ss>20)
        {
          comenzar=0;
          aumentar=4;
        }
    }
     while(aumentar==4)
    {   
        if(seteo1==0)break;
        desaceleracion(18,17,800,4,2);
        printRutinaBasico(2,2);
        if(mm>=1 && ss>30)
        {
          comenzar=0;
         vel = FreqCount.read()*2*3.1416/(21*0.104);
         recorrido=0.01*vel*0.105*(mm*60+ss);
         desaceleracion(16,14,1000,3,2);
         pinMode(2,OUTPUT);
         digitalWrite(2,LOW);
         guardar();
         aumentar=0;
         contador=0;
         comenzar=0;
         seteo1=0;
        }
    }
     
  }
  while(seteo1==3)
  {
    if(comenzar==0){
      ss=0;
      mm=0;
      hh=0;
    }
    rampa(0,17,100,1,3);
    printRutinaBasico(3,3);
    if (ss>20)
    { 
      comenzar=0;
      aumentar=1;
    }
    while(aumentar==1)
    {   
        if(seteo1==0)break;
        rampa(17,18,800,2,3);
        printRutinaBasico(3,3);
        if(ss>40)
        { 
          comenzar=0;
          aumentar=2;
        }
    }
    while(aumentar==2)
    {   
        if(seteo1==0)break;
        rampa(18,19,800,2,3);
        printRutinaBasico(3,3);
        if(mm>=1)
        {
         comenzar=0;
          aumentar=3;
        }
    }
     while(aumentar==3)
    {   
        if(seteo1==0)break;
        desaceleracion(19,18,800,4,3);
        printRutinaBasico(3,3);
        if(mm>=1 && ss>20)
        {
          comenzar=0;
          aumentar=4;
        }
    }
      while(aumentar==3)
    {   
        if(seteo1==0)break;
        desaceleracion(18,17,800,2,3);
        printRutinaBasico(3,3);
        if(mm>=1 && ss>40)
        {
          comenzar=0;
          aumentar=4;
        }
  }
      while(aumentar==4)
    {   
        if(seteo1==0)break;
        desaceleracion(17,16,800,4,3);
        printRutinaBasico(3,3);
        if(mm>=2)
        {
         comenzar=0;
         vel = FreqCount.read()*2*3.1416/(21*0.104);
         recorrido=0.01*vel*0.105*(mm*60+ss);
         desaceleracion(16,14,1000,3,3);
         pinMode(2,OUTPUT);
         digitalWrite(2,LOW);
         guardar();
         aumentar=0;
         contador=0;
         comenzar=0;
         seteo1=0;
        }
  }
  }
  while (seteo1==4)
  {
     if(k>comparar)
    { 
      if(comenzar==0)comenzar=0;
      if(comenzar==0 && k==1){
      ss=0;
      mm=0;
      hh=0;
      }
      rampa(comparar+16,k+16,100,2,4);
      printRutinaBasico(4,4);
    }else if(k==0)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      sprintf(frase,"E. Libre ");
      lcd.print(frase);
      lcd.setCursor(0,1);
      sprintf(frase,"0:0");
      lcd.print(frase);
      mostrar_resultados();
      delay(200);
    }
  }

}




void printRutinaBasico(int operacion,int t)
{  
    lcd.clear();
    lcd.setCursor(0,0);
    funcion(operacion);
    lcd.print(frase);
    printDate();
    mostrar_resultados();
    delay(300);
    lcd.clear();
    lcd.setCursor(0,0);
    rutina_tiempo(t);
    lcd.print(frase);
    printDate();
    mostrar_resultados();
    delay(300);
}

void rutina_tiempo(int modo)
{
  switch (modo)
{
  case 1:
  sprintf(frase,"Dur. 1 min ");
  break;
  case 2:
  sprintf(frase,"Dur. 1 min y 30 sec ");
  break;
  case 3:
  sprintf(frase,"Dur. 2 min ");
  break;
  case 4:
  sprintf(frase,"          ");
} 
}


void mostrar_resultados()
{
  if(contador1==0)
  {
    vel = FreqCount.read()*2*3.1416/(21*0.104);
    count=vel;
  }else if(contador1==1)
  {
    DateTime now=rtc.now();
    recorrido=0.01*vel*0.105*(mm*60+ss);
    count=recorrido;
  }else if(contador1==2)
  {
    calorias=recorrido*peso;
    count=calorias;
  }
     lcd.setCursor(6,1);
     lcd.print(count);
  if(contador1==0)sprintf(frase," rpm");
  else if(contador1==1)sprintf(frase," m");
  else if(contador1==2)sprintf(frase," cal");
     lcd.print(frase);
}


void funcion(int e)
{
  switch(e)
  {
    case 1:
    sprintf(frase,"E. Basico ");
    break;

    case 2:
    sprintf(frase,"E. Medio ");
    break;

    case 3:
    sprintf(frase,"E. Fuerte ");
    break;

    case 4:
    sprintf(frase,"E. Libre ");
  }
  
}

void printDate()
{ 
  if (ss>59)
  {
    ss=0;
    mm++;
  }
  if (mm>59)
  {
    mm=0;
    hh++;
  }
  lcd.setCursor(0,1);
  sprintf(frase,"%d:%d",mm,ss);
  lcd.print(frase);
}

void rampa(int a,int b,int c,int d,int g)
{
    if(comenzar==0)
    {
      for(i=a;i<b;i++)
    {
      analogWrite(2,i);
      caso_rampa(d,g);
      delay(c);
      comenzar=1;
      if(seteo1==0)break;
    }
    }else
    {
      analogWrite(2,i);
      mostrar_resultados();  
    }
}

void desaceleracion(int a,int b,int c,int d,int g)
{
    if(comenzar==0)
    {
      for(j=a;j>b;j--)
    {
      analogWrite(2,j);
      caso_rampa(d,g);
      delay(c);
      comenzar=1;
      if(seteo1==0)break;
    }
    }
    else
    {
      analogWrite(2,j);
      mostrar_resultados();
    }
}

void caso_rampa(int caso,int f)
{
  switch (caso)
  {
  case 1:
    lcd.clear();
    lcd.setCursor(0,0);
    funcion(f);
    lcd.print(frase);
    lcd.setCursor(0,1);
    sprintf(frase,"Comenzando... ");
    lcd.print(frase);
    break;

  case 2:
    lcd.clear();
    lcd.setCursor(0,0);
    funcion(f);
    lcd.print(frase);
    lcd.setCursor(0,1);
    sprintf(frase,"Aumentando... ");
    lcd.print(frase);
    break;

   case 3:
    lcd.clear();
    lcd.setCursor(0,0);
    funcion(f);
    lcd.print(frase);
    lcd.setCursor(0,1);
    sprintf(frase,"Apagando... ");
    lcd.print(frase);
    break;

    case 4:
    lcd.clear();
    lcd.setCursor(0,0);
    funcion(f);
    lcd.print(frase);
    lcd.setCursor(0,1);
    sprintf(frase,"Disminuyendo... ");
    lcd.print(frase);
    break;
  }
}

void Interrupcion()
{
  delay(100);
  a=digitalRead(52);
  b=digitalRead(53);
  if(a==LOW && b==HIGH)
  {
    if(medir_peso==0)peso++;
    else if(seteo1==4)
      {
        comenzar=0;
        comparar=k;
        k=k+1;
        if(k>3)k=3;
      }else
    {
     contador++;
    if(contador>3)contador=0; 
    }
  }
  else if(a==HIGH && b==LOW)
  {
    if(seteo1!=0 && medir_peso>0)
    {
      contador1++;
      if(contador1>2)contador1=0;
      }else peso--;
  }
  
  else if(a==LOW && b==LOW)
  {
    if (medir_peso==0)medir_peso=1;
    else if(seteo1>0)
    {   
        comenzar=0;
        vel = FreqCount.read()*2*3.1416/(21*0.104);
        recorrido=0.01*vel*0.105*(mm*60+ss);
        desaceleracion(i,1,1000,3,seteo1);
        pinMode(2,OUTPUT);
        digitalWrite(2,LOW);
         aumentar=0;
         contador=0;
         comenzar=0;
         seteo1=0;
    }
    else{
      if (contador==1)seteo1=1;
      else if(contador==2)seteo1=2;
      else if (contador==3)seteo1=3;
      else seteo1=4;
    }
  }
}

void segundo()
{
  ss++;
}

void guardar()
{
 float t_lunes,t_martes,t_miercoles,t_jueves,t_viernes,t_sabado,t_domingo,r_lunes,r_martes,r_miercoles,r_jueves,r_viernes,r_sabado,r_domingo;
 float tiempo=mm+ss/60;
 DateTime now=rtc.now();
 if(now.day()==leer.dia && now.month()==leer.mes && now.year()==leer.anio)
 {
    if(now.dayOfTheWeek()==1)
    {
      t_lunes=leer.ti_lunes+tiempo;
      r_lunes=leer.re_lunes+recorrido;
    }else if(now.dayOfTheWeek()==2)
    {
      t_martes=leer.ti_martes+tiempo;
      r_martes=leer.re_martes+recorrido;
    }else if(now.dayOfTheWeek()==3)
    {
      t_miercoles=leer.ti_miercoles+tiempo;
      r_miercoles=leer.re_miercoles+recorrido;
    }else if(now.dayOfTheWeek()==4)
    {
      t_jueves=leer.ti_jueves+tiempo;
      r_jueves=leer.re_jueves+recorrido;
    }else if(now.dayOfTheWeek()==5)
    {
      t_viernes=leer.ti_viernes+tiempo;
      r_viernes=leer.re_viernes+recorrido;
    }else if(now.dayOfTheWeek()==6)
    {
      t_sabado=leer.ti_sabado+tiempo;
      r_sabado=leer.re_sabado+recorrido;
    }else if(now.dayOfTheWeek()==0)
    {
      t_domingo=leer.ti_domingo+tiempo;
      r_domingo=leer.re_domingo+recorrido;
    }
 }else
 {
     if(now.dayOfTheWeek()==1)
    {
      t_lunes=tiempo;
      r_lunes=recorrido;
    }else if(now.dayOfTheWeek()==2)
    {
      t_martes=tiempo;
      r_martes=recorrido;
    }else if(now.dayOfTheWeek()==3)
    {
      t_miercoles=tiempo;
      r_miercoles=recorrido;
    }else if(now.dayOfTheWeek()==4)
    {
      t_jueves=tiempo;
      r_jueves=recorrido;
    }else if(now.dayOfTheWeek()==5)
    {
      t_viernes=tiempo;
      r_viernes=recorrido;
    }else if(now.dayOfTheWeek()==6)
    {
      t_sabado=tiempo;
      r_sabado=recorrido;
    }else if(now.dayOfTheWeek()==0)
    {
      t_domingo=tiempo;
      r_domingo=recorrido;
    }
 }
 int ad=0;
 datos escribir={
  now.day(),
  now.month(),
  now.year(),
  t_lunes,
  t_martes,
  t_miercoles,
  t_jueves,
  t_viernes,
  t_sabado,
  t_domingo,
  r_lunes,
  r_martes,
  r_miercoles,
  r_jueves,
  r_viernes,
  r_sabado,
  r_domingo,
 };
 EEPROM.put(ad,escribir);
}


