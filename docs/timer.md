# STM32 Timers

## Introduction to timers

- What exactly is a Timer?
  - Its one of the peripheral of the Micro controller.
- What are the uses of a Timer?
  - Time base generation.
  - Measuring/counting input signal frequency (measuring time periods of waveforms)
  - Producing different Waveforms.
  - Measuring pulses width.
  - Generating pulse width modulation (PWM) signals.
  - triggering external devices.
- What does a timer do?
  - A timer at the basic level just **counts** from 0 to some pre-programmed value (up counting) or from some programmed value to 0 (down counting).

- What is the time gap (time period)?
  - Its is time the timer is counting a time, that is depending upon the clock frequency of the timer peripheral.

- When the programmed value is archived, it starts over and when it rolls over to zero, it actually produces an event and that event is called as update event and that update event is registered in the status register of the timer peripheral. And it also has the capacity to interrupt the processor.

## Type of the timers

- Basic Timers (available in all STM32 MCUs).
- General purpose timer (available in all STM32 MCUs).
- Advanced timer (not available in all STM32 MCUs).

## PWM introduction

- Pulse width modulation. It's actually modulating the width of a pulse or you can say that modulating the period of wave or signal.

- In the digital circuit or in the digital world, for example, if you consider the micro-controller's digital pin, then logical 0 means 0 volt, and 1 means 3.3 volt, then a GPIO is a Digital Entity. if you want 0 -> connect to GND, you want 1 held to VCC.

- If you want to get an output in between 0 and 3.3volt, the PWM is best method.

- By using PWM mode, generate PWM signals of 25%, 45%, 75% and 90% Duty cycle on a timer channel.
