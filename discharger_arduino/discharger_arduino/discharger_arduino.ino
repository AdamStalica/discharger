

String a;

void setup() {
	Serial.begin(115200);
}
void loop() {
	while (Serial.available()) {
		a = Serial.readString();

		Serial.println(a);
	}
}
