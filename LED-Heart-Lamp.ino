int ledPin = 9;
int potPin = A0;
int fadeAmount = 2; // Amount to fade in each cycle
int minBrightness = 30;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  static int brightness = minBrightness;
  static int brightnessOut = 0; // led brightness signal
  static boolean fadingUp = true;
  
  if (fadingUp) {
    brightness += fadeAmount;
    if (brightness >= 255){
      fadingUp = false;
    }
  } else {
    brightness -= fadeAmount;
    if (brightness <= 0) {
      fadingUp = true;
    }
  }

  // Read potentiometer value (0->1023~)
  int potValue = analogRead(potPin);  
  Serial.println("pot val: " + String(potValue));

  if (potValue > 900) {
    // set max brightness no fade
    brightnessOut = 255;
  } else if (potValue < 150) {
    // set min brightness as off no fade
    brightnessOut = 0;
  } else {
    // Map pot val (150->900) to PWM range (0->255)
    int potAsPWM = map(potValue, 150, 900, minBrightness, 255);
    brightnessOut = map(brightness, 0, 255, minBrightness, potAsPWM);
  }

  // safety
  if (brightnessOut > 255) {
    brightnessOut = 255;
  } else if (brightnessOut < 0) {
    brightnessOut = 0;
  };
  
  Serial.println("bright val: " + String(brightnessOut));

  // Set LED brightness
  analogWrite(ledPin, brightnessOut); 

  delay(50);
}
