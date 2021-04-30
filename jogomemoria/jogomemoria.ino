String recebido;
String sequenciaNumerica = "";
int led, sequencia, contador = 1, velocidade = 1000;
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
stateGame = 1 -- níveis do jogo (aumenta a velocidade e a quantidade de números 
                 para lembrar - a velocidade aumenta a partir do nível 5 até o 
                 nível 10)
stateGame = 2 -- fim de jogo "Game over"
stateGame = 3 -- jogar novamente?
*/
void loop() {
  switch (stateGame) {
    case 0:
      // inicio de jogo
	  Serial.println("");
      Serial.println("*. INICIO .*");
      Serial.println("Comecar? (s/n)");
      leserial();
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Iniciando...");
        piscaled(1000,3);
      } else {
        stateGame = 0;
        Serial.println("Jogo nao iniciado"); 
        piscaled(300,5);     
      }
      break;
    case 1:
      // Níveis do jogo
	  Serial.println("");
      Serial.println(String("*. Nivel ") + contador + String(" .*"));
      if(contador == 1) {
  		geraSequencia(1000, 3);
    		leserial();
	  }else if(contador < 5){
		geraSequencia(1000, 5); 
		leserial();
      } else {
      	geraSequencia(velocidade, contador); 
		leserial();
	  }
	  if (recebido == sequenciaNumerica){
	    contador = contador + 1;
        Serial.println("Parabens! proximo nivel.");
        piscaled(1000,3);
	    // para ir ficando mais difícil
	    if(contador <= 4){
		  velocidade = velocidade - 70;
		} else if(contador <= 7){
		  velocidade = velocidade - 80;
		} else if(contador < 10){
		  velocidade = velocidade - 95;
		}
      } else {
        stateGame = 2;
        Serial.println("Aaah nao, voce errou!"); 
        piscaled(300,5);     
      }
      break;
    case 2:
      // Game over!!!
	  Serial.println("");
      Serial.println("*.* Game Over *.*"); 
      piscaled(100,5);
      stateGame = 3;
      break;
    case 3:
      Serial.println("jogar novamente? (s/n)"); 
      leserial();
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Jogo comecando...");
	    contador = 1;
        piscaled(1000,3);
      } else {
        stateGame = 4;
        Serial.println("Jogo nao iniciado"); 
        piscaled(300,5);     
      }
      break;
    case 4:
	  Serial.println("");
	  Serial.println("Obrigada por jogar! Ate a proxima :)"); Serial.println("");
	  Serial.println("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"); 
	  contador = 1;
	  stateGame = 0;
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