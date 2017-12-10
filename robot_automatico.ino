//Andrea De Angelis
//robot automatico

#define SensoreSX 0  //sensore SX al pin analogico 0
#define SensoreDX 1  //sensore DX al pin analogico 1

int vdx = 120, vsx = 120, vmax = 130;
float sx, dx, k = 1, kdx = 1, ksx = 1;
int E1 = 6, E2 = 5;  //controllo potenza motori
int M1 = 7, M2 = 4;  //controllo direzione motore
	
void setup() {
  Serial.begin(9600);
  pinMode(SensoreSX, INPUT);
  pinMode(SensoreDX, INPUT);
  pinMode(M1, OUTPUT);   
  pinMode(M2, OUTPUT);
}
void loop() {
    //lettura valori sensori
  sx = analogRead(SensoreSX);
  dx = analogRead(SensoreDX);
    //faccio il rapporto tra il valore del sensore sx e destro e lo moltiplico per il coefficente k
  vdx = (sx/dx)*k*vmax;  
    //se kdx>1 lo pongo = 1 perchè poi questo valore sarà moltiplicato per la velocità massima per impostare la velocità del motore di dx
  if (vdx >= 255) {
    vdx = 255;
  }
  vsx = (dx/sx)*k*vmax;
  if (vsx >= 255) {
    vsx = 255;
    
  }
    //moltiplico i rapporti tra i 2 sensori per la velocità massima dei motori per impostare la nuova velocità dei motori
  //vsx = vmax*ksx;
  //vdx = vmax*kdx;
  
    //imposto senso di marcia del robot (avanti)
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
    //imposto velocità motori
  analogWrite(E1, vdx);  //motore destro
  analogWrite(E2, vsx);  //motore sinistro
}
