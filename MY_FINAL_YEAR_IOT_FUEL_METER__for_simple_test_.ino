int n = 0;
float vol = 0.0,l_minute;
unsigned char flowsensor = 2;
unsigned long currentTime;
unsigned long cloopTime;
int flow_frequency;
float prev_val =0;
float vol_arr[] = {};
void flow () 
{
   flow_frequency++;
}

void setup() 
{
  Serial.begin(9600);
  pinMode(flowsensor,INPUT);
  digitalWrite(flowsensor, HIGH); 
  attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); 
  currentTime = millis();
  cloopTime = currentTime;
}

void loop() 
{
   currentTime = millis();
   if(currentTime >= (cloopTime + 1000))
   {
    cloopTime = currentTime; 
    if(flow_frequency != 0)
    {     
      l_minute = (flow_frequency / 7.3); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      l_minute = l_minute/60;
      vol = vol +l_minute;
      Serial.print("Vol:");
      Serial.print(vol);
      Serial.println("L");
      flow_frequency = 0; // Reset Counter
      Serial.print("flow rate:");
      Serial.print(l_minute, DEC); // Print litres/hour
      Serial.println(" L/Sec");      
    }
   
   else
    { 
      Serial.print("max_volume = ");
      Serial.println(vol);
      if(vol>0)
        {          
//        delay(10);
        Serial.println("Sent to database successfully");
        Serial.print("data sent to database is = ");
        Serial.println(vol);
        }
      vol = 0;
      Serial.println(" flow rate = 0 ");
      Serial.print("Vol:");
      Serial.print(vol);
      Serial.println(" L");
    }
    }     
}
