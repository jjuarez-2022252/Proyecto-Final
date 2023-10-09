const int sensor= A2; // Sensor FZ0430 conectado al ping A0
int sensorvalue;      // Variable que almacena el valor de 0 a 1023
float V;              // Almacena el voltaje de 0.0 a 25.0


//Variables Amperaje
//Sensibilidad del sensor

float SEN = 0.185; // Para el sensor de 5 A
int SAMPLESNUMERO = 100;

//Variables Resistencia 

int sensorPn = A3;    
int valorsensor;
float voltaje, r1, r2;

void setup() {
 Serial.begin(9600);
 //Resistencia 
 r2 = 10000; // R2 = 10KΩ
}

void loop() {

  // sensor de voltaje
  sensorvalue= analogRead(sensor); //Realiza la lectura
  V= fmap(sensorvalue,0,1023,0.0,25.0); // cambia a 0.0 - 25
  Serial.print("Voltaje = ");
  Serial.println(V); // imprime la variable 
  

  // fin sensor de voltaje
  // Inicio sensor de amperaje

  float current = getCorriente(SAMPLESNUMERO);
  float currentRMS = 0.707 * current; 
  float power = 230.0 * currentRMS;

   printm("intensidad", current, "A ,");
   printm("Irms", currentRMS, "A . ");
   printm("Potencia", power, "W");
   

   //Fin Sensor de amperaje
  // Inicio Resistencia 

  float R2 = 10000;
  float Vout = analogRead(A2);
  float Vout2= map(Vout,0,1023,0,500000);
  float Vout3= Vout2/100000;
  float V1 = (R2*5) / Vout3;
  float R1 = V1 - R2;
  R1=R1+9;
  Serial.println();
  Serial.print("Valor aproximado de R1 = ");
  Serial.println(R1);
  delay(3000);
}

//Sensor de voltaje 
// Cambio de escala para dar lectura mas precisa 
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
 
}
// fin sensor de voltaje 

// Sensor de amperaje
void printm( String prefix, float value1, String postfix)
{
  Serial.print(prefix);
  Serial.print(value1, 3);
  Serial.print(postfix);
  
}

float getCorriente(int SN){
  float VOLTAJE;
  float corriente = 0;

  for(int i=0; i < SN; i++)
  {
    VOLTAJE = analogRead(A1) * 5.0 / 1023.0;
    corriente += (VOLTAJE -2.5) / SEN;
  }
  return(corriente / SN);
}
