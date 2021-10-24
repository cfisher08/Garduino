// Settings
const int boneDrySoilMoisturemV = 1100;
const int fullySaturatedAndDrainedSoilMoisturemV = 5000;

// Enums Settings
// Range is assigned if soilMoisturePercentageSmoothed is less than the setting percentage but greater than the level below it.
// i.e. soilMoisturePercentageSmoothed = 10 => VeryDry
//      soilMoisturePercentageSmoothed = 55 => Moist
enum SoilMoistureRange {
  VeryDry = 25,
  Dry = 50,
  Moist = 75,
  VeryMoist = 100
};

// Variables
float soilMoistureVoltage = 0.0;
float soilMoistureVoltageSmoothed = 0.0;
int soilMoisturemiliVoltageSmoothed = 0;
float soilMoisturePercentageSmoothed = 0.0;
SoilMoistureRange soilMoistureRange = VeryDry;



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Workflow:
  // Read Moisture Sensor Signal: (AI0)
  soilMoistureVoltage = readAIVoltage(0);

  // Smooth Signal:
  soilMoistureVoltageSmoothed = soilMoistureVoltage;

  // Convert To Linear Scale Percent
  soilMoisturemiliVoltageSmoothed = (int)soilMoistureVoltageSmoothed * 1000;
  if (soilMoisturemiliVoltageSmoothed < boneDrySoilMoisturemV) {
    soilMoisturePercentageSmoothed = 0.0;
  }
  else if (boneDrySoilMoisturemV <= soilMoisturemiliVoltageSmoothed && soilMoisturemiliVoltageSmoothed < fullySaturatedAndDrainedSoilMoisturemV) {
    soilMoisturePercentageSmoothed = (soilMoisturemiliVoltageSmoothed - (float)boneDrySoilMoisturemV) / ((float)fullySaturatedAndDrainedSoilMoisturemV - (float)boneDrySoilMoisturemV) * 100;
  }
  else {
    soilMoisturePercentageSmoothed = 100;
  }

  // Assign Range {Very Dry, Dry, Moist, Very Moist}:

  // Save Values to Report:

  // Read Temperature Sensor Signal:
  // Smooth Signal:
  // Convert To Engineering Units:
  // Assign Range {Cold, Normal, Hot}:
  // Save Values to Report:

  // Read Light Sensor Signal:
  // Smooth Signal:
  // Convert To Engineering Units:
  // Assign Range {Night, Low Light, Ambient/Day Overcast, Bright Indirect, Full Sun}

  // Take Action
  // Report Comms

  // Delay Loop

  // ====================================================================================

  // To Read AI   ==>
  //                    Use analogRead Function to read sensor
  //                    sensorValue between 0, 1023
  //                    int sensorValue = analogRead(AIPinID)

  // To Write AO  ==>
  //                    Use analogWrite Function to write to AO
  //                    inputValue between 0, 255
  //                    analogWrite(AOPinID, inputValue);
  //                    NOTE: If feeding back from sensor. use map
  //                      to rescale from 0-1023 to 0-255
  //                    scaledValue = map(sensorValue, 0, 1023, 0,255);

}

float readAIVoltage(int aiID) {
  // Returns voltage of aiPin as float point value:

  int sensorValue = analogRead(aiID);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  return voltage;
}

void writeAOVoltage(int aoID, float voltage) {
  // Writes voltage to aoPinOut. Assuming voltage range is 0-5V
  // Limiter statement for out of range voltage commands

  if (voltage < 0.0) {
    Serial.print("voltage must be greater than 0.0V");
  }
  else if (voltage > 5.0) {
    Serial.print("voltage must be less than 5V");
  }
  else {
    int outputValue = map(voltage, 0, 5, 0, 255);
    analogWrite(aoID, outputValue);
  }
}