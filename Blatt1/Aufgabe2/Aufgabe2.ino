int led = 13;  // led to use for output (13 is built-in)

int dit_delay = 500;           // length of a dit in ms
int dah_delay = dit_delay * 3; // length of a dah in ms

// dit() and dat() already include dit_delay
int letter_delay = dah_delay - dit_delay;

// letters already include letter delay
int word_delay   = dit_delay * 7 - letter_delay;

void dit() {
    Serial.print(".");

    // send a dit
    digitalWrite(led, HIGH);
    delay(dit_delay);

    digitalWrite(led, LOW);
    delay(dit_delay);
}

void dah() {
    Serial.print("-");
  
    // send a dah
    digitalWrite(led, HIGH);
    delay(dah_delay);

    digitalWrite(led, LOW);
    delay(dit_delay);
}

void pause_letter() {
   Serial.println("");
   delay(letter_delay);
}

void pause_word() {
   Serial.println("");
   delay(word_delay);
}

void morse_S() {
    dit(); dit(); dit();
    pause_letter();
}

void morse_I() {
    dit(); dit();
    pause_letter();
}

void morse_N() {
    dah(); dit();
    pause_letter();
}

void morse_K() {
    dah(); dit(); dah();
    pause_letter();
}

void morse_SINK() {
    morse_S(); morse_I(); morse_N(); morse_K();
    pause_word();
}

// send n in morse code
void morse_digit(int n) {
    Serial.print("morse_digit(");
    Serial.print(n);
    Serial.println(")...");

    if (n == 0) {
        dah(); dah(); dah(); dah(); dah();
    }
    if (n == 1) {
        dit(); dah(); dah(); dah(); dah();
    }
    if (n == 2) {
        dit(); dit(); dah(); dah(); dah();
    }
    if (n == 3) {
        dit(); dit(); dit(); dah(); dah();
    }
    if (n == 4) {
        dit(); dit(); dit(); dit(); dah();
    }
    if (n == 5) {
        dit(); dit(); dit(); dit(); dit();
    }
    if (n == 6) {
        dah(); dit(); dit(); dit(); dit();
    }
    if (n == 7) {
        dah(); dah(); dit(); dit(); dit();
    }
    if (n == 8) {
        dah(); dah(); dah(); dit(); dit();
    }
    if (n == 9) {
        dah(); dah(); dah(); dah(); dit();
    }
    pause_letter();
    
    Serial.print("morse_digit(");
    Serial.print(n);
    Serial.println(")...done");
}

void morse_number(int n) {
    Serial.print("morse_number(");
    Serial.print(n);
    Serial.println(")...");
  
    if (n >= 10) {
        morse_number(n / 10);
    }
    morse_digit(n % 10);

    Serial.print("morse_number(");
    Serial.print(n);
    Serial.println(")...done");
}


void morse_H()
{
  dit();dit();dit();dit();
  pause_letter();
}

void morse_A() 
{
  dit();dah();
  pause_letter();
}

void morse_L() 
{
  dit();dah();dit();dit();  
  pause_letter();
}

void morse_O() 
{
  dah();dah();dah();
  pause_letter();
}

void morse_W() 
{
  dit();dah();dah();    
  pause_letter();
}

void morse_E() 
{
  dit();  
  pause_letter();
}

void morse_T() 
{
  dah();
  pause_letter();
}


void hallowelt()
{
  morse_H();morse_A();morse_L();morse_L();morse_O();
  pause_word();
  led--; //Ausgabe ab hier auf LED 12
  morse_W();morse_E();morse_L();morse_T();
  pause_word();
  led++; //ausgabe wieder auf LED 13
  
  /*
  Alternativ könnte man dit() und dah() mit einem Parameter für die led versehen, z.b. void dit(int led){}
  und diesen auch in die jeweiligen Funktionen übernehmen, dann also void morse_X(int led){.....dit(led);....} usw.
  
  */
}

void morse_binary(int n) {
  
    if (n >= 2) {
        morse_binary(n / 2);
    }
    if (n % 2 > 0)
   {
     dah();
     Serial.print(1);
   }
   else
   { 
     dit();
     Serial.print(0);     
   } 
}



void setup() {
  // put your setup code here, to run once:
  
  // Configure LED as output
  pinMode(led, OUTPUT);
  pinMode(led + 1, OUTPUT);
  
  // Use serial port as output
  Serial.begin(9600);
}

/*
 Aufgaben:
  1.) Funktionen für die notwendigen Buchstaben ergänzt, Funktion hallowelt, die alles zusammen ausgibt
  2.) siehe FUnktion hallowelt
  3.) morse_binary hinzugefügt
  
*/

void loop() {
  hallowelt();
  morse_binary(128);
}
