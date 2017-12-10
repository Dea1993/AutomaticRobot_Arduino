/* Andrea De Angelis
*  LICENSE GPL-3
*  andrea.deangelis93@gmail.com */

#define SensoreSX A0  // sensore SX al pin analogico 0
#define SensoreDX A1  // sensore DX al pin analogico 1
#define PulsanteAvvio 2 // pulsante di accensione del robot al pin digitale 2
#define LED 3 // LED notifica funzionamento robot al pin digitale 3

int vdx = 0, vsx = 0, vmax = 160; // nella tesina avevo usato vmax 130
float sx, dx; // variabili contenenti il valore letto dalle 2 fotoresistenze (dx e sx)
// questi sono i valori (riportati sulla scheda per il controllo del PWM) per poter controllare velocità e direzione dei 2 motori
// E1 e M1 riguardano potenza e direzione del motore di destra
// E2 e M2 riguardano potenza e direzione del motore di sinistra
int E1 = 6, E2 = 5;  // jumper per il controllo della potenza motori
int M1 = 7, M2 = 4;  // jumper per il controllo della direzione motore
int Pulsante, Luce; // variabili per memorizzare lo stato del PulsanteAvvio e LED
int StatoRobot=0;

void setup() {
  Serial.begin(9600);
  pinMode(SensoreSX, INPUT);  // imposto questo pin in input
  pinMode(SensoreDX, INPUT);  // imposto questo pin in input
  pinMode(PulsanteAvvio, INPUT);  // imposto questo pin in input
  digitalWrite(2, HIGH);
  pinMode(LED, OUTPUT);  // imposto questo pin in output
  digitalWrite(3, LOW);  // spengo il led
  pinMode(M1, OUTPUT);  // imposto questo pin in output
  pinMode(M2, OUTPUT);  // imposto questo pin in output
}
void loop() {
  // leggo i valori rilevati dalle 2 fotoresistenze e li memorizzo nelle apposite variabili
  sx = analogRead(SensoreSX);
  dx = analogRead(SensoreDX);
  Pulsante = digitalRead(PulsanteAvvio);
  Serial.println(StatoRobot);
  // se il pulsante è premuto avvio il programma
  if (Pulsante==LOW) {
    if (StatoRobot==0) {
      // dico al software che il robot deve mettersi in movimento
      StatoRobot=1;
      digitalWrite(3, HIGH);  // accendo il led
    } else {
      // dico al software che il robot si deve fermare
      StatoRobot=0;
      digitalWrite(3, LOW);  // spengo il led
    }
    // introduco un delay per dar tempo all'utente di rilasciare il pulsante altrimenti il robot potrebbe accendersi e poi rispegnersi immediatamente
    delay(300);
  }

  // verifico quale è lo stato del robot
  if (StatoRobot==1) {
    // calcolo la velocità del motore di destra in base al rapporto tra i valori letti dai 2 sensori
    vdx = (sx/dx)*vmax;
    // se il valore supera la velocità massima dei motori, lo setto alla sua velocità massima (255)
    if (vdx >= 255) {
      vdx = 255;
    }
    // se il valore di vdx scende sotto 0, lo imposto a 0
    if (vdx < 0) {
      vdx = 0;  // imposto a 0 la velocità del motore sinistro
    }
    
    // calcolo la velocità del motore di sinistra in base al rapporto tra i valori letti dai 2 sensori
    vsx = (dx/sx)*vmax;
    // se il valore supera la velocità massima dei motori, lo setto alla sua velocità massima (255)
    if (vsx >= 255) {
      vsx = 255;
    }
    // se il rapporto è inferiore a 0 setto la velocità a 0
    if (vsx < 0) {
      vsx = 0;  // imposto a 0 la velocità del motore sinistro
    }
    
    // imposto senso di marcia del robot (LOW=avanti HIHG=indietro)
    digitalWrite(M1, LOW);  // motore destro
    digitalWrite(M2, LOW);  // motore sinistro
    
    // imposto velocità motori
    analogWrite(E1, vdx);  // motore destro
    analogWrite(E2, vsx);  // motore sinistro
  } else {
    // se lo stato del robot è a 0, allora faccio fermare il robot impostando a 0 la velocità dei 2 motori
    // imposto velocità motori
    analogWrite(E1, 0);  // motore destro
    analogWrite(E2, 0);  // motore sinistro
  }
}
