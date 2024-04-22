#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU        16000000UL  // Clock frequency
#define PRESCALER_US 1           // Prescaler for microseconds
#define PRESCALER_MS 64          // Prescaler for milliseconds
#define SEC_TO_US    1000000UL   // us per second
#define SEC_TO_MS    1000        // ms per second

class Timer {
public:
    enum TimerNum { TIMER_0, TIMER_1, TIMER_2 };
    enum TimeUnit { MILLIS, MICROS };

    Timer(TimerNum num, TimeUnit unit); // Constructor
    void init();
    void start();
    void stop();
    void reset();
    volatile unsigned long overflow_counter;
    static Timer* timer_ptr; // Pointer to the timer instance

private:
    TimerNum _num;
    TimeUnit _unit;
    void _init_timer_0();
    void _init_timer_1();
    void _init_timer_2();

    // Constants for OCR0A and OCR2A to achive low latency
    static constexpr uint32_t _ocr_micros = ((F_CPU / SEC_TO_US / PRESCALER_US) - 1);
    static constexpr uint32_t _ocr_millis = ((F_CPU / SEC_TO_MS / PRESCALER_MS) - 1);
};

#endif