
/***************************************************************************
  This is a library for the BMP3XX temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP388 Breakout
  ----> http://www.adafruit.com/products/3966

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

#include <SD.h>
#include <Adafruit_BMP3XX.h>
#include <bmp3.h>
#include <bmp3_defs.h>



#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)


// this might just be the BMP_CS thing but we will see

File myFile;


Adafruit_BMP3XX bmp;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Adafruit BMP388 / BMP390 test");

  if (!bmp.begin_I2C()) {   // hardware I2C mode, can pass in address & alt Wire
  //if (! bmp.begin_SPI(BMP_CS)) {  // hardware SPI mode  
  //if (! bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI)) {  // software SPI mode
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }
  

 if (SD.exists("testing.txt")) {
    Serial.println("Removing example.txt...");
    SD.remove("testing.txt");
  }



if(!SD.begin(10)){

  Serial.print("Card Failed, or not present");
  while(1);
}








  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

void loop() {
  if (! bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

/*
Serial.println("Initializing SD Reading...THIS TIME AT THE LOOP");
*/
if(!SD.begin(10)){

  Serial.print("Card Failed, or not present");
  while(1);
}

/*
Serial.println("Initialization was good G LETS GOOOO");
*/

myFile = SD.open("testing2.txt", FILE_WRITE);

// now this will happen if the file opened okay which is the writing portion
if (myFile){

Serial.println(" YES IT OPENED WE WILL NOW WRITE INTO THE FILE ");

myFile.print("Pomona Tempurature= ");
myFile.print(bmp.temperature*(9/5) +32);
myFile.println(" *F");

myFile.print("Pomona Pressure = ");
myFile.print(bmp.pressure/6894.76);
myFile.println(" Psi");

myFile.print("Pomona Approx. Altitude = ");
myFile.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
myFile.println(" m");
myFile.println("DATE IS 11/30/2023");

myFile.close();
Serial.println("YOOOOO WE PRINTED AND CLOSED IT");
}
else {
//this is the warning if the file did not open
Serial.println("the testing file did not open FOR PRINTING");
}


// Im now opening the file again to read some of the data we have put in 
/*
myFile = SD.open("testing.txt");
if (myFile){

Serial.println("The testing.txt: ");

while(myFile.available()){
Serial.write(myFile.read());
}

myFile.close();

}
else {
// this will print if the file could not open for reading
Serial.println("the testing file could not open for READING");
}
*/



  Serial.print("Temperature = ");
  Serial.print(bmp.temperature*(9/5) +32);
  Serial.println(" *F");

  Serial.print("Pressure = ");
  Serial.print(bmp.pressure/6894.76);
  Serial.println(" Psi");

  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");


//REMEMBER TO FIX THE TIMING HERE EXTREMELY IMPORTANT TO FIX TIME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 2000
  Serial.println();
  delay(5000);









}