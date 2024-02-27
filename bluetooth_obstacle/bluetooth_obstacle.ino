// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int vpin = 3;
// defines variables
long duration;
int distance;
int checking = 0;
int state = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(vpin, OUTPUT); // Sets the vpin as an Output
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
  }

  
  if(state == '0') {
    state = 0;
    checking = 0;
    analogWrite(vpin, 0);
  }

  if(state == '1' && checking == 0) {
    checking = 1;
    state = 0;
  }

  if(checking) {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;

    int freq;
    if(distance > 400) freq = 0;
    else freq = 256 - 0.63*distance;
    
    analogWrite(vpin, freq);
    delayMicroseconds(50);
  }
}
