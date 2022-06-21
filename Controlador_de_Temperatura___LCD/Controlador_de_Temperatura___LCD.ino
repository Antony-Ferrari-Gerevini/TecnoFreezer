#include <LiquidCrystal.h>                  //inclui biblioteca para ligar o LCD

const int sensorTemperatura = A0;           //constantes para elementos do sistema
const int motor = 8;

int pot1 = A1;                              //variáveis para seleção do potenciômetro
int pot2 = A2;

int sensor = 0;                             //variáveis para dados
int temperatura = 0;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);    //saídas do LCD

void setup()                                //informando o que cada elemento vai fazer (INPUT/OUTPUT)
{
  pinMode((pot1),INPUT);        
  pinMode((pot2),INPUT);
  
  pinMode(sensorTemperatura, INPUT);
  pinMode(motor, OUTPUT);
  
  Serial.begin(9600);
  
  lcd_1.begin(16, 2); 
  
}

void loop(){
  
  
  lcd_1.setCursor(0, 0);                   //posição no LCD em que a informação será printada
  pot1=analogRead(A1);                     //leitura do potenciômetro
  
  if (pot1>=0&&pot1<=255){                 //controla o que será printado no LCD
      lcd_1.print("Coca Cola ->->");}
  
  if (pot1>=256&&pot1<=511){
      lcd_1.print("Pepsi ->->");}
  
  if (pot1>=512&&pot1<=800){
      lcd_1.print("Fanta L ->->");}
  
  if (pot1>=800&&pot1<=1024){  
      lcd_1.print("Guarana ->->");}
 
  
  
  lcd_1.setCursor(0, 1);        //mesmo sistema de LCD, só que printando na segunda linha
  pot2=analogRead(A2);
  
  if (pot2>=0&&pot2<=255){
      lcd_1.print("Coca Cola ->->");}
  
  if (pot2>=256&&pot2<=511){
      lcd_1.print("Pepsi ->->");}
  
  if (pot2>=512&&pot2<=800){
      lcd_1.print("Fanta L ->->");}
  
  if (pot2>=800&&pot2<=1024){  
      lcd_1.print("Guarana ->->");}


  sensor = analogRead(sensorTemperatura);                                                //leitura do sensor de temperatura
  temperatura = map(((analogRead(sensorTemperatura) - 20) * 3.04), 0, 1023, -40, 125);
  
  if (temperatura>=-5){                                                                  //controla o estado do motor do freezer
    if (temperatura>=2){
      delay(1000);
      digitalWrite(motor, HIGH);
    }
    if (temperatura<=-4){
      delay(1000);
      digitalWrite(motor, LOW);
    }
  }
  
   
  
  Serial.println(sensor);               //prints para verificar funcionamento do circuito
  Serial.println(temperatura);
  Serial.println("");
  delay(500);

}
