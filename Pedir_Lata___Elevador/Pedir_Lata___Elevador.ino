const int botEsquerdo = 6;                   //constantes do sistema de escolher uma lata
const int botDireito = 7;
const int servoEsqUm = 2;
const int servoEsqDois = 3;
const int servoDirUm = 4;
const int servoDirDois = 5;

const int interruptorBaixo = 12;             //constantes do sistema de elevador
const int interruptorCima = 13;
const int elevadorUm = 10;
const int elevadorDois = 11;
const int sensorLuz = A0;
const int trigPin = 8;
const int echoPin = 9;

bool permissao = true;                       //variáveis necessárias para o funcionamento
bool entregaCheck = false;
int escolha = 0;

void setup(){                                //informando o que cada elemento vai fazer (INPUT/OUTPUT)
  pinMode(botEsquerdo, INPUT_PULLUP);
  pinMode(botDireito, INPUT_PULLUP);
  pinMode(servoEsqUm, OUTPUT);
  pinMode(servoEsqDois, OUTPUT);
  pinMode(servoDirUm, OUTPUT);
  pinMode(servoDirDois, OUTPUT);
  
  pinMode(interruptorBaixo, INPUT_PULLUP);
  pinMode(interruptorCima, INPUT_PULLUP);
  pinMode(elevadorUm, OUTPUT);
  pinMode(elevadorDois, OUTPUT);
  pinMode(sensorLuz, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
}





void loop(){
  
  if (permissao == true){           //verificar os estados dos botões que pedem uma lata
  escolha = aguardando();
    Serial.println(escolha);
  }else if (escolha == 1){
    escolhaEsquerdo();
    escolha = 0;
  }else if (escolha == 2){
    escolhaDireito();
    escolha = 0;
  }
  
  if (permissao == false && escolha == 0){                                                                                       //testa variáveis para saber qual função o elevador deve executar
    if (!digitalRead(interruptorBaixo) == HIGH && analogRead(sensorLuz) <= 10 && entregaCheck == false){                         //quando elevador embaixo com lata
      controlaElevador("Subir");
    }else if (!digitalRead(interruptorCima) == HIGH && calculaDistancia(trigPin, echoPin) <= 10 && entregaCheck == false){       //quando elevador encima com lata
      controlaElevador("Parar");
    }else if (!digitalRead(interruptorCima) == HIGH && calculaDistancia(trigPin, echoPin) > 10 && entregaCheck == false){        //quando elevador encima sem lata
      entregaCheck = true;
      controlaElevador("Descer");
    }else if (!digitalRead(interruptorBaixo) == HIGH && analogRead(sensorLuz) <= 10 && entregaCheck == true){                    //prevenção de bugs
      entregaCheck = false;
    }else if (!digitalRead(interruptorBaixo) == HIGH && analogRead(sensorLuz) > 10 && entregaCheck == true){                     //quando elevador embaixo e entrega feita
      controlaElevador("Parar");
      entregaCheck = false;
      permissao = true;
    }   
  }
}
 

 
  
  
int aguardando(){                                          //leitura dos botões que pedem uma lata
  int e = 0;
  while(true){
    Serial.println(calculaDistancia(trigPin, echoPin));

    if (!digitalRead(botEsquerdo)){
      e = 1;
      break;
    }else if (!digitalRead(botDireito)){
    e = 2;
    break;
    }
  }
  permissao = false;
  return e;
}

void escolhaEsquerdo(){                      //derruba a lata da esquerda no elevador
  digitalWrite(servoEsqUm, HIGH);
  digitalWrite(servoEsqDois, LOW);
  delay(2000);
  digitalWrite(servoEsqUm, LOW);
  digitalWrite(servoEsqDois, HIGH);
  delay(2000);
  digitalWrite(servoEsqDois, LOW);
}

void escolhaDireito(){                       //derruba a lata da direita no elevador
  digitalWrite(servoDirUm, LOW);
  digitalWrite(servoDirDois, HIGH);
  delay(2000);
  digitalWrite(servoDirUm, HIGH);
  digitalWrite(servoDirDois, LOW);
  delay(2000);
  digitalWrite(servoDirUm, LOW);
}

void controlaElevador(String comando){       //faz elevador subir
  if(comando == "Subir"){
    digitalWrite(elevadorUm, HIGH);
    digitalWrite(elevadorDois, LOW);
  }else if(comando == "Descer"){             //faz elevador descer
    digitalWrite(elevadorUm, LOW);
    digitalWrite(elevadorDois, HIGH);
  }else if(comando == "Parar"){              //faz elevador parar
    digitalWrite(elevadorUm, LOW);
    digitalWrite(elevadorDois, LOW);
  }
}
                          
long calculaDistancia(int trigPin, int echoPin){            //leitura do sensor de distância ultrassônico que verifica se a lata foi entregue ou não
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duracao = pulseIn(echoPin, HIGH);
  
  return (duracao/2) / 29.1;
}                      
