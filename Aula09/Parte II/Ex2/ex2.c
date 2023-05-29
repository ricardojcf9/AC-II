
void setPWM(unsigned int dutyCycle)
{
if (dutyCicle >= 0 && dutyCicle <= 100)
{
OC1RS = ((PRX + 1) * dutyCycle) / 100; // Determine OC1RS as a function of "dutyCycle"
}
