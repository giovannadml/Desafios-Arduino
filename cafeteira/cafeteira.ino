#include <Ultrasonic.h>  //importa a biblioteca do sensor ultrassônico

HC_SR04 sensor_compartimento(4,5);   // o sensor da xícara
HC_SR04 sensor_tamanho(2,3);         // o sensor da mão

int servo_compartimento = 9, servo_tamanho = 10;
float dist_tam_atual = sensor_tamanho.distance(), dist_tam_anterior;

void setup() {
  pinMode(servo_compartimento, OUTPUT);  // configura o pino 9 do arduino para o servo_compartimento
  pinMode(servo_tamanho, OUTPUT);        // configura o pino 10 do arduino para o servo_tamanho
  
  Serial.begin(9600);
}

void loop() {

  // mostrando no serial a distância que o sensor está captando
  Serial.println(String("Distância comp: ") + sensor_compartimento.distance() +String(" cm"));
  Serial.println(String("Distancia tam: ") + sensor_tamanho.distance() +String(" cm"));
  
  // armazena em uma variável o valor da distância atual para que seja feita uma lógica de apenas
  // mudar para a seleção de café longo ou curto caso a distância tenha mudado, se não colocar algo
  // assim ele fica acionando em todas as execuções do loop
  dist_tam_anterior = dist_tam_atual;
  dist_tam_atual = sensor_tamanho.distance();

  // se a distancia for menor que 20 cm quer dizer que tem uma xícara de café
  if (sensor_compartimento.distance() < 20){
	// então o compartimento tem que abrir (90° indica o compartimento aberto)
	posicaoServo(servo_compartimento, 90);
	// caso o compartimento esteja aberto, o usuário pode escolher um tamanho de café, curto ou longo.
	// se a distância da mão da pessoa for maior que 30cm, o café é longo (40ml)
	if (dist_tam_anterior != dist_tam_atual && sensor_tamanho.distance() > 30){
	  // então a posição do servo é de 0°
	  posicaoServo(servo_tamanho, 0);
	  delay(500);
	  // e depois volta para a posição de repouso, em 90°
	  posicaoServo(servo_tamanho, 90);
	// se a distância for menor ou igual a 30cm, o café é curto (20ml)
	} else if (dist_tam_anterior != dist_tam_atual && sensor_tamanho.distance() <= 30) {
	  // então a posição do servo é de 180°
	  posicaoServo(servo_tamanho, 180);
	  delay(500);
	  // e depois volta para a posição de repouso, em 90°
	  posicaoServo(servo_tamanho, 90); 
	}
  }
  // se a distância for maior que 20 não tem xícara
  else {
	// então o compartimento deve estar fechado (0° indica o compartimento fechado)
    posicaoServo(servo_compartimento, 0);
	// e como não tem xícara a pessoa não pode escolher o tamanho do café, assim o servo 
	// que escolhe o tamanho fica na posição de repouso, em 90°
	//posicaoServo(servo_tamanho, 90);
  }
  delay(500);
}


void posicaoServo(int servo, int posicao)
{
  int microPulso = map(posicao,0,180,1000,2000);
  digitalWrite(servo, HIGH);
  delayMicroseconds(microPulso);
  digitalWrite(servo, LOW);
  delay(10);                   
}
