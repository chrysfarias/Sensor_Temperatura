#include <LiquidCrystal.h>  
LiquidCrystal LCD(12,11,7,6,5,4);  // Inicializa a biblioteca LCD e define quais pinos digitais serão usados para a entrada do LCD


// inicialização de variáveis que serão utilizadas

int estadoBotao = 0;
float sensor = 0;
float temp_Celsius = 0;
float temp_Fahrenheit = 0;
float maxC = 0; 
float maxF = 0;
float minF = 0;
float minC = 0 ; 


// Atribuição de valores para as portas usadas

#define SENSOR_TEMP A0
#define LED_VERDE 2
#define MEIO_SEGUNDO 500
#define UM_SEGUNDO 1000
#define MOTOR 3
#define LED_VERMELHO_RGB 10
#define LED_AZUL_RGB 9
#define LED_VERDE_RGB 8
#define BOTAO 13




void setup()
{
    Serial.begin(9600);  // comunicação com o monitor Serial
  	iniciaPortas();	 // inicia todas as portas (digitais e analógicas do projeto)
  	acendeled_Inicializacao();  //liga o led verde ao iniciar o dispositivo
  	LCD.clear();  // limpa a tela do LCD
  	
}  
  

void loop()
{  
    leitura_Temperatura();  // função que será repetida dentro do codigo	
  	  
}



  // Define quais portas serão de entrad ou saída de dados
void iniciaPortas(){
  
   pinMode(SENSOR_TEMP ,INPUT);
   pinMode(LED_VERDE,OUTPUT);
   pinMode(LED_VERMELHO_RGB,OUTPUT);
   pinMode(LED_AZUL_RGB,OUTPUT);
   pinMode(LED_VERDE_RGB,OUTPUT);
   pinMode(MOTOR,OUTPUT);
   pinMode(BOTAO,INPUT); 
   
  }
void leitura_Temperatura(){

 
	sensor = analogRead(SENSOR_TEMP);  //leitura do sensor 
    temp_Celsius = map(((analogRead(SENSOR_TEMP) - 20) * 3.04), 0, 1023, -40, 125); // conversao dos valores lidos na porta analogica em valores de escla temperatura
    temp_Fahrenheit = ((temp_Celsius*9+160)/5);
	led_Rgb(temp_Celsius); // chama a função led_Rgb para indicar intervalos de temperaturas críticos
  	checa_Botao(BOTAO);  // chama a função de verificção do estado do botao
  	ligaMotor(temp_Celsius);  // função para ligar o Motor quando necessário
  	
}


   // Acende o lerde Verde ao inicializar o dispositivo
void acendeled_Inicializacao(){
  
  	digitalWrite(LED_VERDE,HIGH);
    delay(MEIO_SEGUNDO);
  	digitalWrite(LED_VERDE,LOW);
    delay(MEIO_SEGUNDO);
  	
}


   // Caso o botão não esteja pressionado, será chamado essa função

void saida_LcdCelsius(float temperaturaCelsius){
  	
    LCD.begin(16,2);
  	LCD.setCursor(0,0);
  	LCD.print("Temp: ");
    LCD.print(temperaturaCelsius,0); 
	LCD.print(" C");  
  	
  
    if (minC == 0){minC = temperaturaCelsius; }
	if (temperaturaCelsius > maxC) {
      maxC = temperaturaCelsius;
    }
  
    if (temperaturaCelsius < minC) {
      minC = temperaturaCelsius;
    }  	
  	
  
    //Mostrando a temperatura máxima
  	LCD.setCursor(0,1);    //(coluna, linha)
 	LCD.print("MX:");
    LCD.print(maxC,0);
	LCD.print(" C");  

  
    //Mostrando a temperatura mínima
  	LCD.setCursor(9,1);  
 	LCD.print("MN:");
    LCD.print(minC,0);
	LCD.print(" C"); 
  	
}



   //indicar intervalos de temperaturas críticos

void led_Rgb(float temperatura){
  
  if ((temperatura > -40) && (temperatura <= 3)){
  	
  		digitalWrite(LED_AZUL_RGB,HIGH);
    	digitalWrite(LED_VERDE_RGB,LOW);
    	digitalWrite(LED_VERMELHO_RGB,LOW);    	     
  }
  
     
   else if ((temperatura > 3) &&(temperatura <= 45) ){
  	
   		digitalWrite(LED_VERDE_RGB,HIGH);
     	digitalWrite(LED_VERMELHO_RGB,LOW);
     	digitalWrite(LED_AZUL_RGB,LOW);
    	delay(UM_SEGUNDO);
     
   }
  
  
  else if((temperatura > 45) &&  (temperatura <= 125)){
  
      digitalWrite(LED_VERMELHO_RGB,HIGH);
      digitalWrite(LED_VERDE_RGB,LOW);
      digitalWrite(LED_AZUL_RGB,LOW);
      delay(UM_SEGUNDO);
   
  } 
}
  
void ligaMotor(float temperatura){
  
    if (temperatura >= 35){
    
      digitalWrite(MOTOR, HIGH);
    
    }
    
     else (digitalWrite(MOTOR,LOW));
  
  }


  
  //Verifica se o Botao está apertado ou não, caso seja mantido pressionado, será mostrado outro sistema de medição de temperatura (F), caso não esteja, será mostrado os valores em Graus (C)

void  checa_Botao(int botao)  { 
  	int estado_Botao = digitalRead(botao); // Verifica se o botão foi pressionado
    delay(UM_SEGUNDO);
  	
  
    if (estado_Botao == 0){
      	LCD.clear();
        
        saida_LcdCelsius(temp_Celsius);
    }
  
    if(estado_Botao ==1){
     	LCD.clear();
    
        saida_LcdFahrenheit(temp_Fahrenheit);	

    }
}


  // Caso o botão esteja pressionado, esta função sera chamada

void saida_LcdFahrenheit(float temperaturaFahrenheit){
  	
    LCD.begin(15,2);
  	LCD.setCursor(0,0);
  	LCD.print("Temp: ");
    LCD.print(temperaturaFahrenheit,0);
	LCD.print(" F");  
  
  
  if (minF == 0) {minF = temperaturaFahrenheit;}
	if (temperaturaFahrenheit > maxF) {
      maxF = temperaturaFahrenheit;
    }
  
    if (temperaturaFahrenheit < minF) {
      minF = temperaturaFahrenheit;
    }  	
  	
  
    //Mostrando a temperatura máxima
  	LCD.setCursor(0,1);    //(coluna, linha)
 	LCD.print("MX:");
    LCD.print(maxF,0);
	LCD.print("F");  

  
    //Mostrando a temperatura mínima
  	LCD.setCursor(10,1);  
 	LCD.print("MN:");
    LCD.print(minF,0);
	LCD.print("F");  	

}
 


	
 

      



  