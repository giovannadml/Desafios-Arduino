// criando as variáveis dos pinos do arduino e as variáveis de estado dos botões
int botao1 = 2, botao2 = 3, pot1 = A0, pot2 = A1, 
botao1Status, botao2Status;

void setup() {
	pinMode(botao1, INPUT_PULLUP);
	pinMode(botao2, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
	botao1Status = digitalRead(botao1);
	botao2Status = digitalRead(botao2);
	
	if (botao1Status == LOW) {
		//Terminal
		Serial.println(String("A") + analogRead(pot1));
		delay(200);
	}
	if (botao2Status == LOW) {
		//Terminal
		Serial.println(String("B") + analogRead(pot2));
		delay(200);
	}
}
