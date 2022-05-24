
// This #include statement was automatically added by the Particle IDE.
#include <Particle_Adafruit_VC0706.h>

// Setup logging
SerialLogHandler logHandler;

/**
 * The two serial connections that can be used to connect to the camera.
 */
ParticleSoftSerial softwareSerialCamPort(/*rx*/ A2, /*tx*/ WKP);
Adafruit_VC0706 softwareSerialCam(&softwareSerialCamPort);

#define hadwareSerialCamPort Serial1
Adafruit_VC0706 hardwareSerialCam(&hadwareSerialCamPort);

// TRUE to set baud via hardware serial, FALSE to test baud via software serial
bool setBaud = true;

void setup() {
  Log.info("Waiting at least 5s for camera to boot");
  delay(5000);
  waitFor(Time.isValid, 30000);

  if (setBaud) {
    Log.info("Trying to set baud via hardware serial");
    if (!hardwareSerialCam.begin()) {
      Log.error("hardwareSerialCam: NOT FOUND");
      Log.error("Cannot set baud.");
      Log.error("Verify camera is correctly wired to hardware serial ports Cam RX -> Photon TX, Cam TX -> Photon RX.");
    } else {
      Log.info("hardwareSerialCam: FOUND");

      char *reply = hardwareSerialCam.getVersion();
      if (reply == 0) {
        Log.error("Failed to get version");
      } else {
        Log.info("\n-----------------\n%s\n-----------------", reply);
      }


      // TODO change to the appropriate BAUD for your use case
      hardwareSerialCam.setBaud19200();
      // TODO change to the appropriate BAUD for your use case
      
      Log.info("hardwareSerialCam: BAUD SET");
      Log.info("Flash with setBaud=false to verify");
    }
  } else {
    Log.info("Trying to verify baud via hardware serial");
    if (!softwareSerialCam.begin(19200)) { // TODO change to appropriate BAUD for your use case
        Log.error("softwareSerialCam: NOT FOUND");
        Log.error("Perhaps the baud was not correctly set.");
        Log.error("Verify camera is correctly wired to hardware serial ports Cam RX -> Photon WKP, Cam TX -> Photon A2.");
        Log.error("Try setting baud again by flashing with with setBaud=true");
      } else {
        Log.info("hardwareSerialCam: FOUND");

        char *reply = hardwareSerialCam.getVersion();
        if (reply == 0) {
          Log.error("Failed to get version");
          Log.error("Try setting baud again by flashing with with setBaud=true");
        } else {
          Log.info("\n-----------------\n%s\n-----------------", reply);
        }
    }
  }
}

void loop() {
  
}