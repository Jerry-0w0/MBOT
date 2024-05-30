// turn LED on for 1 second if button pressed twice w/in 500 msec

#define ON  LOW
#define OFF HIGH

byte butPin = A7;
byte ledPin = 10;

byte butLst;
byte but;

int  butCnt = 0;

unsigned long msec;
unsigned long butMsec;
unsigned long ledMsec;


// -----------------------------------------------------------------------------
void loop (void)
{
    msec = millis ();
    but  = digitalRead (butPin);

    if (butLst != but)  {
        butLst = but;

        if (LOW == but) {   // button pressed
            butCnt++;

            if (msec - butMsec < 500 && 2 <= butCnt)  {
                ledMsec = msec;
                digitalWrite (ledPin, ON);
            }

            butMsec = msec;
            if (1 < butCnt)
                butCnt  = 0;
        }

        delay (10);         // debounce
    }

    if (ledMsec && msec - butMsec > 1000)
        digitalWrite (ledPin, OFF);
        
}

// -----------------------------------------------------------------------------
void setup (void)
{
    digitalWrite (ledPin, OFF);
    pinMode      (ledPin, OUTPUT);

    pinMode      (butPin, INPUT_PULLUP);
    butLst      = digitalRead (butPin);
}