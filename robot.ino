/* By Gayan Kavirathne
 *  29/09/2018
 */

   int velocity = 100;
    // Midlle Sensor  I/O
    #define S0 4
    #define S1 5
    #define S2 6
    #define S3 7
    #define middleSensorOut 8
    int R = 0;
    int G= 0;
    int B = 0;

    /*
     * Middle Sensor colour readings
     * 1 = red;
     * 2 = magenta
     * 3 = greean
     * 4 = pink
     * 5 = yellow
     * 6 = white
     */

    // Side Sensor I/O
    
    #define LS 2      // left sensor
    #define RS 3      // right sensor

    int leftSensorOut;
    int rightSensorOut;
    
    // Motor I/O
    
    #define LM1 9       // left motor
    #define LM2 10       // left motor
    #define RM1 11       // right motor
    #define RM2 12       // right motor

    // Control variables
    int junction = false;  // set true by middle sensor if in a junction
    
    int findColor(int R,int G, int B);
    void setup() {
      pinMode(S0, OUTPUT);
      pinMode(S1, OUTPUT);
      pinMode(S2, OUTPUT);
      pinMode(S3, OUTPUT);
      pinMode(middleSensorOut, INPUT);
      
      // Setting frequency-scaling to 20%
      digitalWrite(S0,HIGH);
      digitalWrite(S1,LOW);

      pinMode(LS, INPUT);
      pinMode(RS, INPUT);
      pinMode(LM1, OUTPUT);
      pinMode(LM2, OUTPUT);
      pinMode(RM1, OUTPUT);
      pinMode(RM2, OUTPUT);
      
      Serial.begin(9600);
    }
    void loop() {
      // Setting red filtered photodiodes to be read
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
      // Reading the output frequency
      R = pulseIn(middleSensorOut, LOW);
      // Printing the value                                                                                                                                                                        on the serial monitor
      Serial.print("R= ");//printing name
      Serial.print(R);//printing RED color frequency
      Serial.print("  ");
      delay(100);
      // Setting Green filtered photodiodes to be read
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
      // Reading the output frequency
      G = pulseIn(middleSensorOut, LOW);
      // Printing the value on the serial monitor
      Serial.print("G= ");//printing name
      Serial.print(G);//printing RED color frequency
      Serial.print("  ");
      delay(100);
      // Setting Blue filtered photodiodes to be read
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
      // Reading the output frequency
      B = pulseIn(middleSensorOut, LOW);
      // Printing the value on the serial monitor
      Serial.print("B= ");//printing name
      Serial.print(B);//printing RED color frequency

      int middleSensorColor = findColor(R,G,B);
      Serial.println(middleSensorColor);
      if(middleSensorColor == 6){
        junction = true;
        }
      Serial.println("  ");
      delay(100);
      delay(1000);

    // IR Sensor Detection 
      leftSensorOut = digitalRead(LS);
      delay(10);
      rightSensorOut = digitalRead(RS);
      delay(10);
      
    // Motor Control 
    Serial.print("Left  " );
    Serial.print(leftSensorOut);
    Serial.print("    Right  ");
    Serial.print(rightSensorOut);
    Serial.println("");

    if(!junction){
        if(leftSensorOut == 1 && rightSensorOut == 1)
        {
          digitalWrite(LM1, HIGH);
          digitalWrite(LM2, LOW);
          digitalWrite(RM1, HIGH);
          digitalWrite(RM2, LOW);
          //break
          delay(velocity);
          digitalWrite(LM1, LOW);
          digitalWrite(LM2, LOW);
          digitalWrite(RM1, LOW);
          digitalWrite(RM2, LOW);
        }
      else if(leftSensorOut == 0 && rightSensorOut == 1)
        {
          digitalWrite(LM1, HIGH);
          digitalWrite(LM2, LOW);
          digitalWrite(RM1, LOW);
          digitalWrite(RM2, HIGH);
          //break
          delay(velocity);
          digitalWrite(LM1, LOW);
          digitalWrite(LM2, LOW);
          digitalWrite(RM1, LOW);
          digitalWrite(RM2, LOW);
        }
     else if(leftSensorOut == 1 && rightSensorOut == 0)
        {
          digitalWrite(LM1, LOW);
          digitalWrite(LM2, HIGH);
          digitalWrite(RM1, HIGH);
          digitalWrite(RM2, LOW);
          //break
          delay(velocity);
          digitalWrite(LM1, LOW);
          digitalWrite(LM2, LOW);
          digitalWrite(RM1, LOW);
          digitalWrite(RM2, LOW);
        }
      }
      else{
          digitalWrite(LM1, HIGH);
          digitalWrite(LM2, LOW);
          
          digitalWrite(RM1, HIGH);
          digitalWrite(RM2, LOW);

          delay(velocity);
          digitalWrite(RM1, LOW);
          digitalWrite(RM2, HIGH);
          // Applying breaks
          delay(1000);
          digitalWrite(LM1, LOW);
          digitalWrite(LM2, LOW);
          digitalWrite(RM1, LOW);
          digitalWrite(RM2, LOW);
          junction = false;
        
        }
      
      }

    

    int findColor(int R,int G, int B){
      //Red
      if(R>=35 && R<= 52 && G>=139 && G<=180 && B>= 107 && B<= 130){
        return 1;
        }
        // Magenta
      else if(R>=72 && R<= 115 && G>=49 && G<=68 && B>= 26 && B<= 42){
        return 2;
        }
        // Green
      else if(R>=57 && R<= 78 && G>=45 && G<=65 && B>= 63 && B<= 90){
        return 3;
        }
        // Pink
      else if(R>=24 && R<= 37 && G>=43 && G<=56 && B>= 32 && B<= 38){
        return 4;
        }
        // Yellow
      else if(R>=26 && R<= 31 && G>=31 && G<=38 && B>= 33 && B<= 45){
        return 5;
        }
        // White
      else if(R>=26 && R<= 44 && G>=28 && G<=40 && B>= 26 && B<= 33){
        return 6;
        }
      else{
        return -1;
        }
      }
