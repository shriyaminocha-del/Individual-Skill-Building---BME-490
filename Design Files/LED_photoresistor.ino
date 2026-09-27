// pin constants
const int buttonPin = 2;
const int ledPin = 9;        
const int photoPin = A0;

bool ledState = false;
bool lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  analogWrite(ledPin, 0);
}

void loop() {

  // reading the button
  bool buttonState = digitalRead(buttonPin);

  // detect button press
  if (buttonState == LOW &&
      lastButtonState == HIGH &&
      millis() - lastDebounceTime > debounceDelay) {

    ledState = !ledState;
    lastDebounceTime = millis();
  }

  lastButtonState = buttonState;


  // read photoresistor
  int lightLevel = analogRead(photoPin);

  Serial.println(lightLevel);


  // control the brightness of the LED
  if (ledState) {

    int brightness = map(lightLevel, 200, 700, 0, 255);

    brightness = constrain(brightness, 0, 255);

    analogWrite(ledPin, brightness);

  } else {

    analogWrite(ledPin, 0);

  }

  delay(10);
}