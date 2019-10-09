/* Code to test the close loop system to control a LED intensity. */

// Include here the PID Library that you have downloaded previously. 
// ------------- WRITE HERE THE CODE--------------------------------- //

// Definition of a boolean variable. If true, it prints the system information each 10 ms in a clean format to copy&paste the info at an excel sheet.
// Otherwise, it prints the information each 100 ms (PID default execution).
bool ziegler_nichols = true;

// Auxiliar variables to read the desired light from the keyboard (function NewConfigParameter() ).
String cadena;
double number;

// Define variables we'll be connecting the PID to.
// Which we will use so as to know the behaviour of our plant (setpoint, input, output)
// ------------- WRITE HERE THE CODE--------------------------------- //

// Define time auxiliar variables
unsigned long Time = 0, Time_ant = 0;
unsigned long num_aux = 0;

// Configuration of the PID Variables that we will change so as to control the plant. And construction of the PID object.
// ------------- WRITE HERE THE CODE--------------------------------- //
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// Configuration of the PID Variables that we will change so as to control the plant. 
void NewConfigParameter()
{
  if (Serial.available() > 0)
  {
    // Meter la lectura en un String
    cadena = Serial.readString();
    // Si el inicio del string es un número, se convierte en float dentro de la variable number
    number = cadena.toFloat();
    Setpoint = number;
  }
}

// The setup routine runs once when you press reset:
void setup() 
{
  // Initialize serial communication at 57600 bits per second 
  Serial.begin(57600);
  // Turn the PID on
  // ------------- WRITE HERE THE CODE--------------------------------- //
    
  // Indicate that we the PID has been activated 
  Serial.println("PID habilitado");
}

// The loop routine runs over and over again forever:
void loop() 
{
    // Read the current time in milliseconds
    Time = millis();

    // Read the input of the channel 0, where we have the LDR connected
    Input = map(analogRead(0), 0, 1023, 0.0, 255.0);
                             
    // Read the Setpoint value using the serial port
    NewConfigParameter();
  
    // Execute the PID controller. The function returns a value of 1 if the PID has been executed. Otherwise, returns a 0
    // ------------- WRITE HERE THE CODE--------------------------------- //
  
    // We want to Write an analog value so as to turn on or off the LED, depending on the PID Output 
    // ------------- WRITE HERE THE CODE--------------------------------- //                                              
    
    // Run the program at 10 ms.   
    //==================================================================================================
    if (Time - Time_ant >=  10)
    { 
        // Auxiliar flag used to print out every 10 ms
        num_aux = 1;
        // Update the variable named Time_ant so as to be able to run the program again after 10 ms. 
        Time_ant = Time;
    }
    //==================================================================================================
  
    // Print out the data if we have tuned the PID or not. 
    //==================================================================================================
    // If we are tunning the PID, print the info each 10 ms to copy the data to an excel file.
    if (ziegler_nichols == true) 
    {
        if (num_aux == 1) {
            // Print out Time in ms.
            Serial.print(Time);
            Serial.print("; ");
            // Print setpoint
            Serial.print(Setpoint);
            Serial.print("; ");
            // Print out the plant output without maping it
            Serial.print(Input);
            Serial.print("; ");
            // Print out PID output, plant input.
            Serial.print(Output);
            Serial.println("; ");
            // Restart the flag.
            num_aux = 0;
        }
    }
    // Ohterwisw, print only when the PID has been executed.
    else 
    {
        if (PID_executed == true) 
        {
            // Print out Time in ms.
            Serial.print("Time = ");
            Serial.print(Time);
            Serial.print("\t ");
            // Print Setpoint
            Serial.print("Setpoint = ");
            Serial.print(Setpoint);
            Serial.print("\t ");
            // Print out the plant output without maping it
            Serial.print("Input = ");
            Serial.print(Input);
            Serial.print("\t ");
            // Print out PID output, plant input.
            Serial.print("Output = ");
            Serial.println(Output);
            // Restart the flag.
            PID_executed = false;
        }
    }
    //==================================================================================================
}  
