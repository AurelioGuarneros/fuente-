
#include <TimerOne.h>
#define Led 5
#define PIN9 6
unsigned long AnchoPulso=1000,Periodo=2000,Frecuencia;

void setup() 
{
pinMode(Led,OUTPUT);
pinMode(PIN9,OUTPUT);
Serial.begin(9600); 
//Timer1.initialize(1000000); 
Timer1.initialize(1000); 

Timer1.attachInterrupt( BajoaAlto); 
//Serial.println(1000000.0/Periodo);
 EscribeFrecuencia();
}

void loop()
{
  if(Serial.available()>0)
{ 
LeeSerie();
}

}


void LeeSerie()
{
  String x,Com;
  int I,n;
  char c;
  unsigned long v;

  delay(100);
  Serial.flush();

char Comando[2];
Serial.readBytes(Comando,2);
Com=String(Comando[0])+String(Comando[1]);

//Com=char(Serial.read())+char(Serial.read());
//Serial.println(char(Serial.read()));
n=Serial.available();
char DatoRec[n];
Serial.readBytes(DatoRec,n-1);
x=DatoRec;

//for(I=0;I<n-1;I=I+1)
  //  {
  //    x=x+DatoRec[I];
 //   }

    
v=x.toInt();

//***********************************************************
 // Serial.print("Comando ");
 // Serial.print( x );
 // Serial.println( ":");
//***********************************************************
  if(Com=="FR")
  {  
 Frecuencia=v;
 Periodo=1000000.0/v;
 AnchoPulso=Periodo/2;
 }

  //***********************************************************
  if(Com=="AP")
  {  
 AnchoPulso=v;
 if(AnchoPulso>Periodo){AnchoPulso=Periodo;}
   }
 //***********************************************************
  if(Com=="PE")
 { Serial.print(v); 
 Periodo=v;
 AnchoPulso=Periodo/2;
 } 

 EscribeFrecuencia() ;
 LimpiaSerial();
 return;  
  
}
void EscribeFrecuencia()
{
Serial.print("FR Frecuencia de ");
 Serial.print(1000000/Periodo);
 Serial.print("Hz (cliclos/seg).\t\tPE Periodo de ");
 Serial.print(Periodo);
 Serial.print(" microsegundos");
 Serial.print(".\t\tAP Pulso ");
 Serial.print(AnchoPulso);
 Serial.print(" microsegundos.\n");

}  
void LimpiaSerial()
{
  while (Serial.available()>0)
  {
    Serial.read();
  }

}




void BajoaAlto()
{
digitalWrite(PIN9,0); 
digitalWrite(Led,1); 
Timer1.attachInterrupt( AltoaBajo,AnchoPulso  );

}
void AltoaBajo()
{
digitalWrite(Led,0);
digitalWrite(PIN9,1); 
 

Timer1.attachInterrupt( BajoaAlto,Periodo-AnchoPulso);

}  


//***********************************************************************************

String Derecha( String C, int N)
{
  int l=C.length();
  String R=C.substring(l-N,l);
  // Serial.println(l); //C.substring(l-N,1+N));

  // Serial.println(R);
  return R;
}
//***********************************************************************************
String Izquierda( String C, int N)
{
  int l=C.length();
  String R=C.substring(0,N);
  // Serial.println(l); //C.substring(l-N,1+N));

  // Serial.println(R);
  return R;
}


//**********************************************************
