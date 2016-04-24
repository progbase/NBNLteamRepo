void IsCarIn()
{
	int isIn;
	int pin;
	const int MaxLightLeveL; // When a car is in
	int lightLevel = analogRead(pin);
	if(lightLevel < MaxLightLeveL) // IS IN
		isIn = 1;
	else
		isIn = 0;
	return isIn;
}