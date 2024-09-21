#include "../include/mpu6050.hpp"
#include <array>
#include <libhal/timeout.hpp>
#include <libhal-util/i2c.hpp>
using namespace std::chrono_literals;

mpu6050::mpu6050(hal::i2c& p_i2c, hal::steady_clock& p_clock, hal::serial& p_terminal) : m_i2c(p_i2c), m_clock(p_clock), m_terminal(p_terminal){
    hal::print(m_terminal, "before setup");
    setup();
}

void mpu6050::setup(){
   // hal::print(m_terminal, "Intial Offset: ");
   // hal::delay(m_clock, 10ms);
    //serial:: wait for user (look at this later)
    //serial:: set timer between each input
    
    //talk with mpu6050 to use function no_sleep

   
//      static constexpr hal::byte expected_device_id = 0x68;
//   // Read out the identity register
//   auto device_id =
//     hal::write_then_read<1>(m_i2c,
//                             addresses::MPU_addr,
//                             std::array{ addresses::WHO_AM_I },
//                             hal::never_timeout())[0];

//   if (device_id != expected_device_id) {
//     hal::safe_throw(hal::no_such_device(m_address, this));
//   }

    
    mpu6050::no_sleep();
    hal::print(m_terminal, "no sleep complete");
    mpu6050::accel_config();
    hal::print(m_terminal, "accel complete");
    hal::print(m_terminal, "after setup");
    //mpu6050::intialize_servo();


}
 void mpu6050::read_xy(){

    // WHO AM I returns 0x68
    // hal::write(m_i2c, addresses::MPU_addr, std::array<hal::byte, 1>{addresses::WHO_AM_I});
    // std::array<hal::byte, 1> a;
    // hal::read(m_i2c, addresses::MPU_addr, a);

    // return;
    std::array<hal::byte, 4> data;
    
    hal::write(m_i2c, addresses::MPU_addr, std::array<hal::byte, 1>{addresses::ACCEL_XOUT_H});
    hal::read(m_i2c, addresses::MPU_addr, data);

    X_out = ((data[0] << 8) | data[1]); // this makes it so that it reads 8 bits because i2c reads 8 bits at a time 
    X_out = X_out / 16384;  // the value is divided by 16384 because thats the LSB Sensitivity on page 29 of the register 
    Y_out = ((data[2] << 8) | data[3]);
    Y_out = Y_out / 16384;
    //reads ACCEL_XOUT_H, ACCEL_XOUT_H, ACCEL_YOUT_H, ACCEL_YOUT_H
    //shift bits

    //in the default position I want, the x_out value is -1, and y_out is 0
    X_out+=1;

    //Change X_out and Y_out to angles
    X_out=X_out*100;
    Y_out=Y_out*100;
    
    
    
 }



void mpu6050::no_sleep(){
    // mpu6050::start();
    // hal::write(m_i2c, addresses::MPU_addr, std::array<hal::byte, 1> {addresses::start_address});

    hal::print(m_terminal,"sent start\n");
    hal::write(m_i2c, addresses::MPU_addr, std::array<hal::byte, 2> {addresses::start_address, modes::no_sleep_var});
    //makes sure the mput6050 doesnt randomly turn off sleep stuff
    //write to 0x6B
    //write to 0x00
}

void mpu6050::accel_config(){
    hal::write(m_i2c, addresses::MPU_addr, std::array<hal::byte, 2>{addresses::ACCEL_CONFIG, 0x00});
    //write to 0x1B
    //write to 0x10
}


void mpu6050::servo_point_up(){
    
    //hal::position(start_angle + user_offset - Y_out); //servo always pointing up
}

void mpu6050::initialize_servo(){
    //intialize
    //hal::position(start_angle);
    hal::delay(m_clock, 10ms);
}