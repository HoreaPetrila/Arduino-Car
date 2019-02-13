#include <NewPing.h>

#define TRIG_PIN 8 
#define ECHO_PIN 7
#define DISTANTA_MAX 400 // distanta pana la care senzorul masoara distanta
#define DISTANTA_COLIZIUNE 20 // distanta de coliziune la care robotul face stop si da inapoi este de : 20cm
NewPing sonar(TRIG_PIN, ECHO_PIN, DISTANTA_MAX);

// L298n module
// 1(+)inainte dreapta = DrFr
// 2(+)inapoi dreapta = DrSp
// 3(+)inainte stanga = StFr
// 4(+)inapoi stanga = StSp
int executieDans=1;
int DrFr = 5;
int DrSp = 4;
int StFr = 3;
int StSp = 2;

void setup() {
  Serial.begin(9600);
  pinMode(DrFr, OUTPUT);
  pinMode(StFr, OUTPUT);
  pinMode(DrSp, OUTPUT);
  pinMode(StSp, OUTPUT);
  digitalWrite(DrFr, LOW);
  digitalWrite(StFr, LOW);
  digitalWrite(DrSp, LOW);
  digitalWrite(StSp, LOW);

  
 
  
}

int scan() {
  return (sonar.ping() / US_ROUNDTRIP_CM); //masurare distanta in cm
}

void loop() {
  //Aici se intampla dansul, o singura executare 
  //la fiecare pornire a masinii

  if(executieDans==1){
    Dans();
    executieDans=0;
  }
  int dist = scan(); 
  if (dist < DISTANTA_COLIZIUNE) {
    STOP();
    mersSpate();
    delay(500);
    virajDreapta();
    delay(300);
  }
  else {
    mersFata();
  }
}

void Dans(){
  mersFata();
  mersSpate();
  virajDreapta();
  mersFata();
  STOP();
}

void STOP() {
  digitalWrite(DrFr, LOW);
  digitalWrite(StFr, LOW);
  digitalWrite(DrSp, LOW);
  digitalWrite(StSp, LOW);
}

void mersFata() {
  digitalWrite(DrFr, HIGH);
  digitalWrite(StFr, HIGH);
  digitalWrite(DrSp, LOW);
  digitalWrite(StSp, LOW);
}

void mersSpate() {
  digitalWrite(DrFr, LOW);
  digitalWrite(StFr, LOW);
  digitalWrite(DrSp, HIGH);
  digitalWrite(StSp, HIGH);
}

void virajDreapta() {
  digitalWrite(DrFr, LOW);
  digitalWrite(StFr, HIGH);
  digitalWrite(DrSp, HIGH);
  digitalWrite(StSp, LOW);
}

void virajStanga() {
  digitalWrite(DrFr, HIGH);
  digitalWrite(StFr, LOW);
  digitalWrite(DrSp, LOW);
  digitalWrite(StSp, HIGH);
}
