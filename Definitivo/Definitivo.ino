const int MOTOR_IZQ_MASTER = 3;
const int MOTOR_IZQ_DELANTERO = 5;
const int MOTOR_IZQ_TRASERO = 6;
const int MOTOR_DER_MASTER = 10;
const int MOTOR_DER_DELANTERO = 9;
const int MOTOR_DER_TRASERO = 11;
const int VELOCIDAD = 60;
const int trigIzq = 13;
const int echoIzq = 4;
const int trigFro = 7;
const int echoFro = 2;
const int trigDer = 8;
const int echoDer = 12;
const int dista=10;

int tiempoIzq, tiempoFro, tiempoDer;
int distanciaIzquierda, distanciaFrente, distanciaDerecha; // Cambié los nombres de las variables
int cont = 0;
int cont1 = 0;


void setup() {
  pinMode(MOTOR_IZQ_MASTER, OUTPUT);
  pinMode(MOTOR_IZQ_DELANTERO, OUTPUT);
  pinMode(MOTOR_IZQ_TRASERO, OUTPUT);
  pinMode(MOTOR_DER_MASTER, OUTPUT);
  pinMode(MOTOR_DER_DELANTERO, OUTPUT);
  pinMode(MOTOR_DER_TRASERO, OUTPUT);
  Serial.begin(9600);
  pinMode(trigIzq, OUTPUT);
  pinMode(echoIzq, INPUT);
  pinMode(trigFro, OUTPUT);
  pinMode(echoFro, INPUT);
  pinMode(trigDer, OUTPUT);
  pinMode(echoDer, INPUT);
}


void loop() {
  inicio();
}

void inicio() {
  int i, d, c;
  i = promDisIzq();
  d = promDisDer();
  c = promDisCentro();
  Serial.println(i);
  Serial.println(d);
  Serial.println(c);
  entno(c, i, d);
  delay(10);
}

int obtenerDistanciaIzquierda() {
  digitalWrite(trigIzq, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigIzq, LOW);
  tiempoIzq = pulseIn(echoIzq, HIGH);
  distanciaIzquierda = tiempoIzq * 0.034 / 2;
  delay(5);
  return distanciaIzquierda;
}

int obtenerDistanciaFrente() {
  digitalWrite(trigFro, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFro, LOW);
  tiempoFro = pulseIn(echoFro, HIGH);
  distanciaFrente = tiempoFro * 0.034 / 2;
  delay(5);
  return distanciaFrente;
}

int obtenerDistanciaDerecha() {
  digitalWrite(trigDer, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigDer, LOW);
  tiempoDer = pulseIn(echoDer, HIGH);
  distanciaDerecha = tiempoDer * 0.034 / 2;
  delay(5);
  return distanciaDerecha;
}
void entno(int c,int i, int d ){
  delay(15);  
  if(cont==0){
    caminar(); 
    delay(1000);
    detener();
    delay(1000);
    girarIzquierda();
    delay(800);  
    detener();
    delay(1000);
    
    caminar();
    delay(3000);
 
    detener();
    delay(1000);
     
    cont++;
  }else if(c<=4 && d>4){
    girarDerecha(); 
    retroceder();
  }else if(c<=3 && d>10 && i>4){
    girarDerecha();
    retroceder();
  }else if(c<=4 && i>4){
   girarIzquierda();
   retroceder();

  
  }else if(c>=5){
    caminar();
    girarIzquierda();
    delay(300);
     caminar();  
  }
}

void girarIzquierda() {
  // Implementa la lógica para girar a la izquierda
   analogWrite(MOTOR_IZQ_MASTER, VELOCIDAD);
  analogWrite(MOTOR_IZQ_DELANTERO, VELOCIDAD);
  analogWrite(MOTOR_IZQ_TRASERO, 0);
  analogWrite(MOTOR_DER_MASTER, 0);
  analogWrite(MOTOR_DER_DELANTERO, 0);
  analogWrite(MOTOR_DER_TRASERO, 0);
}

void caminar() {
  // Implementa la lógica para avanzar
   analogWrite(MOTOR_IZQ_MASTER, VELOCIDAD);
  analogWrite(MOTOR_IZQ_DELANTERO, VELOCIDAD);
  analogWrite(MOTOR_IZQ_TRASERO, LOW);
  analogWrite(MOTOR_DER_MASTER, VELOCIDAD);
  analogWrite(MOTOR_DER_DELANTERO, VELOCIDAD);
  analogWrite(MOTOR_DER_TRASERO, LOW);
}

void girarDerecha() {
  // Implementa la lógica para girar a la derecha
   analogWrite(MOTOR_IZQ_MASTER, 0);
  analogWrite(MOTOR_IZQ_DELANTERO, 0);
  analogWrite(MOTOR_IZQ_TRASERO, 0);
  analogWrite(MOTOR_DER_MASTER, 0);
  analogWrite(MOTOR_DER_DELANTERO, VELOCIDAD);
  analogWrite(MOTOR_DER_TRASERO, VELOCIDAD);
}

void retroceder() {
  // Implementa la lógica para retroceder
  analogWrite(MOTOR_IZQ_MASTER, VELOCIDAD);
  analogWrite(MOTOR_IZQ_DELANTERO, LOW);
  analogWrite(MOTOR_IZQ_TRASERO, VELOCIDAD);
  analogWrite(MOTOR_DER_MASTER, VELOCIDAD);
  analogWrite(MOTOR_DER_DELANTERO, LOW);
  analogWrite(MOTOR_DER_TRASERO, 0);
}
  void detener() {
  // Implementa la lógica para girar a la derecha
   analogWrite(MOTOR_IZQ_MASTER, 0);
  analogWrite(MOTOR_IZQ_DELANTERO, 0);
  analogWrite(MOTOR_IZQ_TRASERO, 0);
  analogWrite(MOTOR_DER_MASTER, 0);
  analogWrite(MOTOR_DER_DELANTERO, 0);
  analogWrite(MOTOR_DER_TRASERO, 0);
}


int promDisCentro() {
  int c = 0, a;
  for (int i = 0; i < 10; i++) {
    delay(2);
    c += obtenerDistanciaFrente();
  }
  a = c / 10;
  return a;
}

int promDisDer() {
  int c = 0, a;
  for (int i = 0; i < 10; i++) {
    delay(2);
    c += obtenerDistanciaDerecha();
  }
  a = c / 10;
  return a;
}

int promDisIzq() {
  int c = 0, a;
  for (int i = 0; i < 10; i++) {
    delay(2);
    c += obtenerDistanciaIzquierda();
  }
  a = c / 10;
  return a;
}

void arreglarIzquierda() {
    analogWrite(MOTOR_DER_MASTER, 0);
  analogWrite(MOTOR_DER_DELANTERO, 0);
  analogWrite(MOTOR_DER_TRASERO, 0);
  
  // Girar hacia la izquierda
  analogWrite(MOTOR_IZQ_MASTER, 50);
  analogWrite(MOTOR_IZQ_DELANTERO, 50);
  analogWrite(MOTOR_IZQ_TRASERO, 50);
  delay(1000);  // Ajusta el tiempo según sea necesario para girar el robot

  // Detener los motores después de un tiempo de giro
  analogWrite(MOTOR_IZQ_MASTER, 0);
  analogWrite(MOTOR_IZQ_DELANTERO, 0);
  analogWrite(MOTOR_IZQ_TRASERO, 0);
  
  // Corregir la orientación (girar en sentido opuesto)
  analogWrite(MOTOR_IZQ_MASTER, -50); // Motor izquierdo en sentido opuesto
  analogWrite(MOTOR_IZQ_DELANTERO, -50); // Motor izquierdo en sentido opuesto
  analogWrite(MOTOR_IZQ_TRASERO, -50); // Motor izquierdo en sentido opuesto
  delay(1000);  // Ajusta el tiempo según sea necesario para corregir la orientación

  // Detener los motores después de corregir la orientación
  analogWrite(MOTOR_IZQ_MASTER, 0);
  analogWrite(MOTOR_IZQ_DELANTERO, 0);
  analogWrite(MOTOR_IZQ_TRASERO, 0);


}

void arreglarDerecha() {
 
  
  analogWrite(MOTOR_IZQ_MASTER, 0);
  analogWrite(MOTOR_IZQ_DELANTERO, 0);
  analogWrite(MOTOR_IZQ_TRASERO, 0);
  
  // Girar hacia la derecha
  analogWrite(MOTOR_DER_MASTER, 50);
  analogWrite(MOTOR_DER_DELANTERO, 50);
  analogWrite(MOTOR_DER_TRASERO, 50);
  delay(1000);  // Ajusta el tiempo según sea necesario para girar el robot

  // Detener los motores después de un tiempo de giro
  analogWrite(MOTOR_DER_MASTER, 0);
  analogWrite(MOTOR_DER_DELANTERO, 0);
  analogWrite(MOTOR_DER_TRASERO, 0);
  
  // Corregir la orientación (girar en sentido opuesto)
  analogWrite(MOTOR_DER_MASTER, -50); // Motor derecho en sentido opuesto
  analogWrite(MOTOR_DER_DELANTERO, -50); // Motor derecho en sentido opuesto
  analogWrite(MOTOR_DER_TRASERO, -50); // Motor derecho en sentido opuesto
  delay(1000);  // Ajusta el tiempo según sea necesario para corregir la orientación

  // Detener los motores después de corregir la orientación
  analogWrite(MOTOR_DER_MASTER, 0);
  analogWrite(MOTOR_DER_DELANTERO, 0);
  analogWrite(MOTOR_DER_TRASERO, 0);

}