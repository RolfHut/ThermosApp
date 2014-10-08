bool debug = FALSE;

//hardware
int heaterPin = D7; //assuming relay that operates a heater on this pin
int sensorPin = A4; //assuming TMP36 sensor on this pin.

//constants
double refVoltage = 3.3; //Voltage used as reference for analogRead
double temperatureStep = 0.5; //(increase, or decrease) step for every call to setTemperature

//variables
double measuredTemperature = 17.0;
double targetTemperature = 17.0;
int heaterStatus = 0;




void setup() {
    //start Serial communication for debugging
    if (debug){
        Serial.begin(9600);
    }


    
    //set lamp
    pinMode(heaterPin,OUTPUT);
    pinMode(sensorPin,INPUT);
    digitalWrite(heaterPin,heaterStatus);
    
    //define communication with cloud
    Spark.function("setTemp",setTemperature);
    Spark.variable("temp",&measuredTemperature, DOUBLE);
    Spark.variable("targetTemp",&targetTemperature, DOUBLE);
    Spark.variable("status",&heaterStatus, INT);
    

}

void loop() {
    //measure the temperature
    getTemperature();
    
    //change heaterStatus if needed
    if (measuredTemperature < targetTemperature){
        heaterStatus = 1;
    } else {
        heaterStatus = 0;
    }

    //write the heaterStatus to the pin with the relay to the heater.
    digitalWrite(heaterPin,heaterStatus);
    

    delay(1000);

    
}

int setTemperature (String command){
    if (command=="hotter"){
        targetTemperature = targetTemperature + temperatureStep;
        return 1;
    } else if (command=="colder"){
        targetTemperature = targetTemperature - temperatureStep;
        return 1;
    } else {
        return -1;
    }
}

int getTemperature(){
    double sensorValue = (double) analogRead(sensorPin);
    if (debug){
        Serial.println(sensorValue);
    }
    double measuredVoltage = refVoltage * sensorValue / 4096.0;
    if (debug){
        Serial.println(measuredVoltage);
    }
    //lo-pass filter (AR1)
    measuredTemperature = (0.9 * measuredTemperature) + (0.1 * ((measuredVoltage - 0.5) * 100.0));
    //rounding to tenth of degree
    measuredTemperature = 0.1 * (round(measuredTemperature * 10));
    if (debug){
        Serial.println(measuredTemperature);
    }

    return 1;
} 
