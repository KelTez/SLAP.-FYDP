#define IR_SENSOR A1

float flameValue = 0;
String underCar = ",";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  flameValue = analogRead(IR_SENSOR)*(3.3/1024.0);
  float distance = 65*pow(flameValue, -1.10);
  Serial.print("under?: ");
  if(distance < 35 && distance > 25){
    underCar = "under";
  }else{
    underCar = "not under";
  }
  Serial.println(underCar);
  Serial.println();
  delay(1500);
  //Serial.println(exp(8.5841-log(val)));
}
