#define SENSOR A0

float val = 0;
String underCar = ",";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(SENSOR)*(3.3/1024.0);
  

  Serial.println(val);
  delay(1500);
  //Serial.println(exp(8.5841-log(val)));

  //whatever range i get, ill need to reduce it slightly i believe
  //need to get actual values. will need to test for new values
}
