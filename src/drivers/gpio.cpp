//======================================================================
// GPIO Driver Class Implementation
//======================================================================
#include "drivers/gpio.h"

#define ENABLE_INPUT(pinType, pin) \
    (*(DDR_FOR_PIN(pinType, pin))  &= ~(1 << BIT_FOR_PIN(pinType, pin)))
#define ENABLE_OUTPUT(pinType, pin) \
    (*(DDR_FOR_PIN(pinType, pin))  |=  (1 << BIT_FOR_PIN(pinType, pin)))
#define ENABLE_PULLUP(pinType, pin) \
    (*(PORT_FOR_PIN(pinType, pin)) |=  (1 << BIT_FOR_PIN(pinType, pin)))

#define DISABLE_INPUT(pinType, pin) \
    (*(DDR_FOR_PIN(pinType, pin))  |=  (1 << BIT_FOR_PIN(pinType, pin)))
#define DISABLE_OUTPUT(pinType, pin) \
    (*(DDR_FOR_PIN(pinType, pin))  &= ~(1 << BIT_FOR_PIN(pinType, pin)))
#define DISABLE_PULLUP(pinType, pin) \
    (*(PORT_FOR_PIN(pinType, pin)) &= ~(1 << BIT_FOR_PIN(pinType, pin)))

#define SET_HIGH(pinType, pin) \
    (*(PORT_FOR_PIN(pinType, pin)) |=  (1 << BIT_FOR_PIN(pinType, pin)))
#define SET_LOW(pinType, pin) \
    (*(PORT_FOR_PIN(pinType, pin)) &= ~(1 << BIT_FOR_PIN(pinType, pin)))
#define TOGGLE(pinType, pin) \
    (*(PORT_FOR_PIN(pinType, pin)) ^=  (1 << BIT_FOR_PIN(pinType, pin)))

//======================================================================
// GPIO Constructor
//======================================================================
GPIO::GPIO(PinType pin_type, uint8_t pin) 
    : _pin_type(pin_type), _pin(pin) {}

//======================================================================
// GPIO Public Methods: enable_output, enable_input, set_high, set_low,
//                      toggle, is_high, is_low
//======================================================================
#define PIN_FOR_PIN(pinType, pin) \
    ((pinType) == DIGITAL_PIN ? (pin < 8 ? &PIND : \
    (pin < 16 ? &PINB : &PINC)) : nullptr)

#define IS_HIGH(pinType, pin) \
    (*(PIN_FOR_PIN(pinType, pin)) & (1 << BIT_FOR_PIN(pinType, pin)))

#define IS_LOW(pinType, pin) \
    !(*(PIN_FOR_PIN(pinType, pin)) & (1 << BIT_FOR_PIN(pinType, pin)))

void GPIO::enable_output() {
    ENABLE_OUTPUT(_pin_type, _pin);
}

void GPIO::enable_input() {
    ENABLE_INPUT(_pin_type, _pin);
}

void GPIO::enable_pullup() {
    ENABLE_PULLUP(_pin_type, _pin);
}

void GPIO::set_high() {
    SET_HIGH(_pin_type, _pin);
}

void GPIO::set_low() {
    SET_LOW(_pin_type, _pin);
}

void GPIO::toggle() {
    TOGGLE(_pin_type, _pin);
}

bool GPIO::is_high() {
    return IS_HIGH(_pin_type, _pin);
}

bool GPIO::is_low() {
    return IS_LOW(_pin_type, _pin);
}