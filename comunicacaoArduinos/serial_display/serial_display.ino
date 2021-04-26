#include <Adafruit_SSD1306.h>

#define OLED_Address 0x3c
Adafruit_SSD1306 oled(128, 64);

int botao1 = 2, botao2 = 3, pot1 = A0, pot2 = A1, dado, botao1Status, botao2Status,
valorPot1 = 0, valorPot2 = 0;

void setup() {	
  //config displau oled
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);

  Serial.begin(9600);
}

void loop() {
	oledDisplay();
	
	if(Serial.available() > 0){				// Se tem alguma coisa no buffer da serial
    	    dado = Serial.read();					// Entao salva em dado
	    
	    if (dado == 'A'){         // Se dado igual a 'A', é o potenciometro1
	      valorPot1 = Serial.parseInt();       // salva em valor o valor do pot1 recebido na serial
	      delay(100);     // delay de 0,1 seg.
	    }
	  
	    if (dado == 'B'){         // Se dado igual a 'B', entao pot2
	      valorPot2 = Serial.parseInt();    // salva em valor o valor do pot2 recebido pela serial
	      delay(100);                         // delay de 0,1 seg.
	    }
	    
	    Serial.println(String("Pot1: ") + valorPot1); 
	    Serial.println(String("Pot2: ") + valorPot2); 

	}
}

void oledDisplay(){
  oled.clearDisplay();
  oled.setCursor(2,2);
  oled.setTextColor(WHITE);
  oled.println(String("Pot1: ") + valorPot1); // Print para mostrar o valor
  oled.println(String("Pot2: ") + valorPot2); // Print para mostrar o valor
}
