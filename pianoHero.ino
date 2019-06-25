
#define erro 13

//os vetores de quando apertar o botão
int reds[25];
int greens[25];
int blues[25];

//variaveis globais
int tempo = 0;
int pontos = 0;
int dificuldade = 0;

//gera cores aleatorias para serem apertadas
void notasAleatorias(){
  for(int i = 0; i < 5; i++){
    reds[i] = 0;
    blues[i] = 0;
    greens[i] = 0;
  }
  for(int i = 5; i < 20; i++){
    int cor = rand()%6;
    reds[i] = cor == 1;
    greens[i] = cor == 2;
    blues[i] = cor == 3;
  }
  for(int i = 20; i < 25; i++){
    reds[i] = 0;
    blues[i] = 0;
    greens[i] = 0;
  }
}

//apaga todos os leds de cor
void apagar(){
  for(int i = 0; i < 12; i++){
    digitalWrite(i,LOW);
  }
}

//acende os leds vermelhos
void red(){
  for(int i = 0; i < 4; i++){
    digitalWrite(i*3,reds[tempo+i]);
  }
}

//acende os leds verdes
void green(){
  for(int i = 0; i < 4; i++){
    digitalWrite(i*3+1,greens[tempo+i]);
  }
}

//acende os leds azuis
void blue(){
  for(int i = 0; i < 4; i++){
    digitalWrite(i*3+2,blues[tempo+i]);
  }
}

//aparece a pontuacao em binario
void pont(int x){
  digitalWrite(9,x%2);
  digitalWrite(6,x%4 >= 2);
  digitalWrite(3,x%8 >= 4);
  digitalWrite(0,x%16 >= 8);
}

void setup() {
  //pega ruido para servir de seed aleatoria
  srand(analogRead(A0));
  notasAleatorias();
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
  
  //espera voce escolher uma dificuldade 
  while (digitalRead(16) == 0 && digitalRead(17) == 0 && digitalRead(18) == 0){}

  //escolhe a dificuldade - facil
  if(digitalRead(16)){
    dificuldade = 1000;
    digitalWrite(11,1);
    digitalWrite(8,1);
    digitalWrite(5,1);
    digitalWrite(2,1);
  }
  //escolhe a dificuldade - medio
  if(digitalRead(17)){
    dificuldade = 750;
    digitalWrite(10,1);
    digitalWrite(7,1);
    digitalWrite(4,1);
    digitalWrite(1,1);
  }
  //escolhe a dificuldade - dificil
  if(digitalRead(18)){
    dificuldade = 500;
    digitalWrite(9,1);
    digitalWrite(6,1);
    digitalWrite(3,1);
    digitalWrite(0,1);
  }
  delay(1000);
}



void loop() {
  
  
  //enquanto a sequencia nao acabar
  if(tempo < 21 ){
    
    //apaga todos os leds
    apagar();
    digitalWrite(erro,LOW);
    
    red();//acende os leds vermelhos
    green();//acende os leds verdes
    blue();//acende os leds azuis
    
    //verifica se acertou
    if(digitalRead(16) == blues[tempo] && digitalRead(17) == greens[tempo] && digitalRead(18) == reds[tempo]){
      pontos++;
    }
    else{
      digitalWrite(erro,HIGH); 
    }

    //incrementa o tempo e espera a proxima cor
    tempo++;
    delay(dificuldade);
  }
  else{
    //mostra os pontos no binario
    pont(pontos/2 );
  }
}
