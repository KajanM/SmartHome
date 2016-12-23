

int val;
int tempPin = 1;
FILE* tempFile;

int temp[10] = { 27,27,27,27,27,27,27,27,27,27 };
int count = 0;
float avg_temp = 27;

void setup()
{
	Serial.begin(115200);
}
void loop()
{

	val = analogRead(tempPin);
	float mv = (val / 1024.0) * 5000;
	float cel = mv / 10;
	float farh = (cel * 9) / 5 + 32;
	if (count < 10)
	{
		//    Serial.print("Avg Temp = ");
		//    Serial.print(avg_temp);
		//    Serial.print("* 10 - temp[");
		//    Serial.print(count);
		//    Serial.print("] +");
		//    Serial.print(cel);
		avg_temp = (avg_temp * 10 - temp[count] + cel) / 10;
		temp[count] = cel;
		count = count + 1;
	}

	else
	{
		count = 0;
		avg_temp = (avg_temp * 10 - temp[count] + cel) / 10;
		temp[count] = cel;
		count = count + 1;
	}

	Serial.print("TEMPRATURE = ");
	Serial.print(avg_temp);
	Serial.print("*C");

	// create file for writing temperature to if it doesn't exist
	tempFile = fopen("/home/root/currentTemperature", "w+");
	// now write to file on the Galileo
	if (tempFile != NULL) {
		// convert float to a string
		fprintf(tempFile, "%.2f", avg_temp);
		fclose(tempFile);
	}
	else {
		Serial.println("File doesn't exist");
	}

	Serial.println();
	delay(1000);

	/* uncomment this to get temperature in farenhite
	Serial.print("TEMPRATURE = ");
	Serial.print(farh);
	Serial.print("*F");
	Serial.println();


	*/
}