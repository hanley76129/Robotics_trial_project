#pragma once

#include <libhal/adc.hpp>
#include <libhal/can.hpp>
#include <libhal/functional.hpp>
#include <libhal/i2c.hpp>
#include <libhal/input_pin.hpp>
#include <libhal/output_pin.hpp>
#include <libhal/pwm.hpp>
#include <libhal/serial.hpp>
#include <libhal/steady_clock.hpp>


struct application_framework
{
  hal::serial* terminal;
  //hal::can* can;
  hal::output_pin* scl;
  hal::output_pin* sda;

  //hal::output_pin* out_pin2;
  //hal::pwm* pwm0;
  //hal::pwm* pwm1;
  // hal::serial* esp;
  //hal::i2c* i2c;
  hal::steady_clock* steady_clock;
  //hal::callback<void()> reset;
};

// Application function must be implemented by one of the compilation units
// (.cpp) files.

application_framework initialize_platform();
void application(application_framework& p_framework);

