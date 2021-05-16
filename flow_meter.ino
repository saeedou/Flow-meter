/* simple code to run yf-s201 flow sensor via Arduino.It will run the sensor
 and print the flow and the valume of our liquid and when the container 90%
 full the ahradware witll generate signal

configuration : red wire to 5 volte
				black wire to GND
				yellow wire to pin 2
				pin 3 will generate the signal*/


volatile int flow_frequency; 
unsigned int l_min; 
unsigned int total_valume;
unsigned int flowsensor = 2; 
unsigned int alarm = 3;
unsigned int container_valume = 200;
unsigned long currentTime;
unsigned long cloopTime;


void flow() 

{
	flow_frequency++;
}


void setup()

{
 
	pinMode(flowsensor, INPUT);
	digitalWrite(flowsensor, HIGH);
	pinMode(alarm,OUTPUT);
	digitalWrite(alarm,LOW); 
	Serial.begin(9600);
	attachInterrupt(0, flow, RISING); 
	sei(); 
	currentTime = millis();
	cloopTime = currentTime;
}

void loop()

{
 currentTime = millis();

if (currentTime >= (cloopTime + 1000)) // Calculate flow and  valume of water 
//once per second
{
	cloopTime = currentTime; // Updates cloopTime
	l_min = (flow_frequency / 7.5); // (Pulse frequency ) / 7.5Q = flowrate
	//in L/minute
	  total_valume += flow_frequency;
	if (total_valume >= 0.9*container_valume) // to turn on the alarm when 90%
		// of the container if full
	{
	  Serial.println("Turn off the faucet");
	  digitalWrite(alarm, HIGH);
	}

	else
	
	{
	Serial.println(flow_frequency,DEC);
	flow_frequency = 0; // Reset Counter
	Serial.print(l_min, DEC); 
	Serial.println(" L/Min");
	Serial.print(total_valume, DEC); 
	Serial.println(" Liter");
	Serial.flush();
    }
  }
}
