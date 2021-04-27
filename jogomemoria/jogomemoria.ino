String recebido;
String sequenciaNumerica = "";
int led, sequencia, contador = 2, velocidade = 1000;
long numeroGerado;
char stateGame = 0;


void setup() {
  // Iniciar comunicacao serie
  Serial.begin(9600);
  // Definir LEDs como OUTPUTs pinos 8,9 e 10
  for(int led = 6; led <= 11; led++){
    pinMode(led, OUTPUT);
  } 
  // Definir a seed do gerador de números aleatórios
  randomSeed(analogRead(0));

}
/*
stateGame = 0 -- inicio do jogo
stateGame = 1 -- jogo nivel1
stateGame = 2 -- jogo nivel2 até onde o usuário conseguir (aumenta a 
				velocidade e a quantidade de números para lembrar depois 
				do nível 5 - a velocidade aumenta até o nível 10)
stateGame = 3 -- fim de jogo "Game over"
stateGame = 4 -- jogar novamente?
*/
void loop() {
  switch (stateGame) {
    case 0:
      // inicio de jogo
      Serial.println("*. INICIO .*");
      Serial.println("Comecar? (s/n)");
      leserial();
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Iniciando...");
        piscaled(1000,3);
      } else {
        stateGame = 3;
        Serial.println("Jogo nao iniciado"); 
        piscaled(300,5);     
      }
      break;
    case 1:
      // Nivel 1 
	  Serial.println("");
      Serial.println("*. Nivel 1 .*");
      geraSequencia(1000, 3); 
      leserial();
      if (recebido == sequenciaNumerica){
        stateGame = 2;
        Serial.println("Parabens! proximo nivel.");
        piscaled(800,3);
      } else {
        stateGame = 3;
        Serial.println("Aaah nao, voce errou!"); 
        piscaled(300,5);     
      }
      break;
    case 2:
      // Nivel 2 
	  Serial.println("");
      Serial.println(String("*. Nivel ") + contador + String(" .*"));
      if(contador < 5){
		geraSequencia(1000, 5); 
		leserial();
      } else {
      	geraSequencia(velocidade, contador); 
		leserial();
	  }
	  if (recebido == sequenciaNumerica){
	    contador = contador + 1;
        stateGame = 2;
        Serial.println("Parabens! proximo nivel.");
        piscaled(1000,3);
	    // para ir ficando mais difícil
	    if(contador <= 6){
		  velocidade = velocidade - 60;
		} else if(contador < 10){
		  velocidade = velocidade - 75;
		} 
      } else {
        stateGame = 3;
        Serial.println("Aaah nao, voce errou!"); 
        piscaled(300,5);     
      }
      break;
    case 3:
      // Game over!!!
      Serial.println("*.* Game Over *.*"); 
      piscaled(100,5);
      stateGame = 4;
      break;
    case 4:
      Serial.println("jogar novamente? (s/n)"); 
      leserial();
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Jogo comecando...");
	    contador = 2;
        piscaled(1000,3);
      } else {
        stateGame = 3;
        Serial.println("Jogo nao iniciado"); 
        piscaled(300,5);     
      }
      break;
  }
}

void leserial(){

  Serial.println("*. Insira sua resposta .*");

  while (Serial.available() == 0)
  {}

  if (Serial.available()) {
    recebido = Serial.readString();
  }
}

void piscaled(int tempo, int vezes){
  for(int i = 0;i < vezes; i++){
    for(int led = 6; led <= 11; led++){
      digitalWrite(led, HIGH);
    }
    delay(tempo);
    for(int led = 6; led <= 11; led++){
      digitalWrite(led, LOW);
    }
    delay(tempo);
  }
}

void geraSequencia (int tempo, int sequencia){
  int ordemLeds[sequencia];

  // Gerar sequencia aleatoria
  for (int i = 0; i < sequencia; i++){
    numeroGerado = random(1, 7);
    ordemLeds[i] = numeroGerado;
  }

  // Inicialmente, a String sequenciaNumerica é uma String vazia
  sequenciaNumerica = "";

  // Pisca os LEDs na sequencia gerada
  for (int j = 0; j < sequencia; j++){
    led = ordemLeds[j];
    if (led == 1){
	  digitalWrite(6, HIGH); delay(tempo); 
	  digitalWrite(6, LOW); delay(tempo);
	}else if (led == 2){
      digitalWrite(7, HIGH); delay(tempo);
      digitalWrite(7, LOW); delay(tempo);
	}else if (led == 3){
      digitalWrite(8, HIGH); delay(tempo);
      digitalWrite(8, LOW); delay(tempo);
    }else if (led == 4){
      digitalWrite(9, HIGH); delay(tempo);
      digitalWrite(9, LOW); delay(tempo);
    }else if (led == 5){
      digitalWrite(10, HIGH); delay(tempo);
      digitalWrite(10, LOW); delay(tempo);
    }else if (led == 6){
      digitalWrite(11, HIGH); delay(tempo);
      digitalWrite(11, LOW); delay(tempo);
    }
  
    sequenciaNumerica = sequenciaNumerica + led;
  }
}