#pragma once

#include <libhal-util/i2c.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>
//#include <libhal/servo.hpp>

class mpu6050{
  public:
    enum addresses : hal::byte{
      MPU_addr = 0x68,
      start_address= 0x6B,
      ACCEL_CONFIG=0x1C,
      ACCEL_XOUT_H=0x3B
    };

    enum modes  : hal::byte{
      no_sleep_var=0x00,
      full_range=0x10,
    };
    
    int start_angle = 90;       // default position of the servo
    int user_offset;            // stores what offset the user wants
    float X_out, Y_out, Z_out;  //variables set up for the info I take out of out of the mpu
    float roll, pitch;          // variable for roll and pitch

    hal::i2c& m_i2c;  
    hal::steady_clock& m_clock;
    hal::serial&   m_terminal;

    mpu6050(hal::i2c& p_i2c,hal::steady_clock& p_clock,hal::serial& p_terminal);

    void no_sleep();
    void start();
    void setup();
    void accel_config();
    void servo_point_up();
    void read_xy(); 
    void initialize_servo();

};