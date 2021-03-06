#include <MicroNMEA.h>
#include <MemoryFree.h>

// Refer to streams logically
Stream& console = Serial;
Stream& gps = Serial1;

char nmeaBuffer[85];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));
bool ledState = LOW;
volatile bool ppsTriggered = false;

void ppsHandler(void);


void ppsHandler(void)
{
  ppsTriggered = true;
}


void gpsHardwareReset()
{
  // Empty input buffer
  while (gps.available())
    gps.read();
  
  digitalWrite(A0, LOW);
  delay(50);
  digitalWrite(A0, HIGH);

  // Reset is complete when the first valid message is received
  while (1) {
    while (gps.available()) {
      char c = gps.read();    
      if (nmea.process(c))
	return;
    }
  }
}

void setup(void)
{
  //Serial.begin(9600); // console
  Serial.begin(115200); // console
  Serial1.begin(9600); // gps
  // Serial1.begin(19200); // gps
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledState);

  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
  console.println("Resetting GPS module ...");
  gpsHardwareReset();
  console.println("... done");
  
  // Compatibility mode off
  // MicroNMEA::sendSentence(gps, "$PONME,2,6,1,0");
  MicroNMEA::sendSentence(gps, "$PONME,,,1,0");

   // Clear the list of messages which are sent.
  MicroNMEA::sendSentence(gps, "$PORZB");

  // Send RMC and GGA messages.
  MicroNMEA::sendSentence(gps, "$PORZB,RMC,1,GGA,1");
  // MicroNMEA::sendSentence(gps, "$PORZB,RMC,1,GGA,1,GSV,1");

#ifdef ARDUINO_AVR_CALUNIUM
  pinMode(6, INPUT);
  attachInterrupt(2, ppsHandler, RISING);
#else
#error Please configure interrupt handler code for alternative board.
#endif

}

void loop(void)
{
  if (ppsTriggered) {
    ppsTriggered = false;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);

    // MicroNMEA::sendSentence(gps, "$PONME,2,6,1,0");
    
    // Output GPS information from previous second
    console.print("Valid fix: ");
    console.println(nmea.isValid() ? "yes" : "no");

    console.print("Nav. system: ");
    if (nmea.getNavSystem())
      console.println(nmea.getNavSystem());
    else
      console.println("none");

    console.print("Num. satellites: ");
    console.println(nmea.getNumSatellites());

    console.print("HDOP: ");
    console.println(nmea.getHDOP()/10., 1);
    
    console.print("Date/time: ");
    console.print(nmea.getYear());
    console.print('-');
    console.print(int(nmea.getMonth()));
    console.print('-');
    console.print(int(nmea.getDay()));
    console.print('T');
    console.print(int(nmea.getHour()));
    console.print(':');
    console.print(int(nmea.getMinute()));
    console.print(':');
    console.println(int(nmea.getSecond()));

    long latitude_mdeg = nmea.getLatitude();
    long longitude_mdeg = nmea.getLongitude();
    console.print("Latitude (deg): ");
    console.println(latitude_mdeg / 1000000., 6);

    console.print("Longitude (deg): ");
    console.println(longitude_mdeg / 1000000., 6);

    long alt;
    console.print("Altitude (m): ");
    if (nmea.getAltitude(alt))
      console.println(alt / 1000., 3);
    else
      console.println("not available");

    console.print("Speed: ");
    console.println(nmea.getSpeed() / 1000., 3);
    console.print("Course: ");
    console.println(nmea.getCourse() / 1000., 3);

#ifdef MEMORY_FREE_H
    console.print("freeMemory()=");
    console.println(freeMemory());
#endif
    console.println("-----------------------");    
    nmea.clear();
  }

  while (!ppsTriggered && gps.available()) {
    char c = gps.read();
    console.print(c);
    nmea.process(c);
  }
  
}
