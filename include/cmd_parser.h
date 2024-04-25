#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#include <avr/io.h>
#include <string.h> // strncmp
#include <stdio.h>  // sscanf

class CMDParser {
public:
    enum Command { NO_CMD, LED_BLINK, LED_ADC, LED_PWR, BUTTON, LED_RAMP };

    CMDParser();
    void parse_cmd(const char* cmd);

    uint8_t  command = LED_BLINK;
    char     cmd_string[20];
    uint16_t cmd_val1;
    uint16_t cmd_val2;
};

#endif // CMD_PARSER_H