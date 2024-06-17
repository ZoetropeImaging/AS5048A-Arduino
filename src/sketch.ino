#include <AS5048A.h>


//AS5048A angleSensor(10);
// Exit to Arduino SS = PIN_SPI_SS (53), Mosi = PIN_SPI_MOSI (51), Miso = PIN_SPI_MISO (50), SCK = PIN_SPI_SCK (52)
AS5048A angleSensor(SS);

// Encoder variables
float AngleCurrent, AnglePrevious, AbsoluteAngle = 0;
float NormalModule = 3;      // The module is normal
float NumberGearTeeth = 17;  // Number of wheel teeth or the number of worms of worm

void setup() {
  Serial.begin(19200);
  ///////////////Filization of the enkoder /////////////////////
  angleSensor.init();
  //AnglePrevious = AngleCurrent = angleSensor.RotationRawToAngle(angleSensor.getRawRotation(true));
  AbsoluteAngle = 0;
  // True inclusion of median average
  // 64 The number of array of measured values ​​for median average
  AnglePrevious = AngleCurrent = angleSensor.RotationRawToAngle(angleSensor.getRawRotation(true, 64));
}

void loop() {
  delay(1000);

  word val = angleSensor.getRawRotation();

  Serial.print("Got rotation of: 0x");
  Serial.println(val, HEX);
  Serial.print("State: ");
  angleSensor.printState();
  Serial.print("Errors: ");
  Serial.println(angleSensor.getErrors());

  Serial.print("Linear");
  Serial.print(getLinearMotion(), 4);
  Serial.println(" mm");
}

// Returns the movement of a straight -toothed of the gear rack in mm
float getLinearMotion() {
  return angleSensor.LinearDisplacementRack(angleSensor.AbsoluteAngleRotation(&AbsoluteAngle, angleSensor.RotationRawToAngle(angleSensor.getRawRotation(true, 64)), &AnglePrevious), NormalModule, NumberGearTeeth);
}
