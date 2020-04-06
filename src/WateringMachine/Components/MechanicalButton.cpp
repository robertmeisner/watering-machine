

#include "MechanicalButton.h"
#include <EdgeDebounceLite.h>


MechanicalButton::MechanicalButton(int pin, ButtonModes mode/*=ButtonModes::MODE_PULLDOWN*/) : _pin(pin), buttonMode(mode)
{}
bool MechanicalButton::init()
{
  pinMode(this->_pin, INPUT);
}
bool MechanicalButton::tick(){

}
void MechanicalButton::setupInterruptHandler(uint8_t irq_pin, void (*ISR)(void), int value)
{
  attachInterrupt(digitalPinToInterrupt(irq_pin), ISR, value);
}
inline void MechanicalButton::handleInterrupt(void)
{
  EdgeDebounceLite debounce;
  byte pinIs = debounce.pin(this->_pin); //Debounce the pin
  if (this->buttonMode == ButtonModes::MODE_PULLUP)
    pinIs = !pinIs; //Reverse the read if Pullup
  switch (this->state)
  {
  case (ButtonStates::STATE_CLOSED):
    if (pinIs == LOW)                                   //If pin is LOW
      this->nextState(ButtonCommand::COMMAND_RELEASED); //Change state to IS_FALLING
    break;
  case (ButtonStates::STATE_IS_FALLING):
    //Do something (The switch has been clicked)
    this->nextState(ButtonCommand::COMMAND_RELEASED); //Change state to IS_OPEN (Not falling anymore)
    break;
  case (ButtonStates::STATE_OPEN):
    if (pinIs == HIGH)                                 //If pin is HIGH
      this->nextState(ButtonCommand::COMMAND_PRESSED); //Change state to IS_RISING
    break;
  case (ButtonStates::STATE_RISING):
    this->nextState(ButtonCommand::COMMAND_PRESSED); //Change state to IS_CLOSED (Not rising anymore)
    break;

  default:
    break;
  }
}
int MechanicalButton::nextState(int command)
{
  ButtonStates nextState = ButtonStates(this->state); // or static_cast<ButtonStates>(this->state);
  switch (command)
  {
  case ButtonCommand::COMMAND_PRESSED:
    if (this->state == ButtonStates::STATE_OPEN)
      nextState = ButtonStates::STATE_RISING;
    else if (this->state == ButtonStates::STATE_RISING)
      nextState = ButtonStates::STATE_CLOSED;
    break;
  case ButtonCommand::COMMAND_RELEASED:
    if (this->state == ButtonStates::STATE_OPEN)
      nextState = ButtonStates::STATE_RISING;
    else if (this->state == ButtonStates::STATE_RISING)
      nextState = ButtonStates::STATE_CLOSED;
    break;
    break;

  default:
    break;
  }
  this->state = nextState;
  return this->state;
}