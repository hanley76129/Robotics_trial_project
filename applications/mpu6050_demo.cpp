
#include <libhal-arm-mcu/stm32f1/output_pin.hpp>
#include <libhal-soft/bit_bang_i2c.hpp> 
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>
#include <libhal/output_pin.hpp>
#include <libhal/units.hpp>
#include <libhal-micromod/micromod.hpp>

#include <libhal-stm32f1/output_pin.hpp>


#include "../include/mpu6050.hpp"
#include "../hardware_map.hpp"

using namespace hal::literals;
using namespace std::chrono_literals;

void application(application_framework &p_framework){
    //auto& i2c2 = *p_framework.i2c;
    auto& clock = *p_framework.steady_clock;
    //auto& terminal = *p_framework.terminal;
    // auto& scl = *p_framework.scl; 
    // auto& sda = *p_framework.sda; 
    auto pin1 = hal::stm32f1::output_pin('A', 0); // work
    auto pin2 = hal::stm32f1::output_pin('A',15);
    auto pin3 = hal::stm32f1::output_pin('B', 3);
    auto pin4 = hal::stm32f1::output_pin('B', 4);
    auto pin5 = hal::stm32f1::output_pin('B', 12); // work
    auto pin6 = hal::stm32f1::output_pin('B',13); // work
    auto pin7 = hal::stm32f1::output_pin('B', 14); // work  
    auto pin8 = hal::stm32f1::output_pin('B', 15);

    


    // hal::soft::bit_bang_i2c bit_bang_i2c({ .sda = &sda, .scl = &scl }, clock);
    //bit_bang_i2c.configure(hal::i2c::settings{ .clock_rate = 100.0_kHz });

    // auto mpu=mpu6050(bit_bang_i2c,clock,terminal);
    // hal::print(terminal, "mpu initialized");
    while(true){
        // mpu.read_xy();
        //prints on the serial monitor
        // hal::print<64>(terminal, "Y= %f degrees", mpu.Y_out);
        // hal::print<64>(terminal, "X = %f degrees", mpu.X_out);
        pin1.level(true);
        pin2.level(true);
        pin3.level(true);
        pin4.level(true);
        pin5.level(true);
        pin6.level(true);
        pin7.level(true);
        pin8.level(true);
        hal::delay(clock, 10ms);

        pin1.level(false);
        pin2.level(false);
        pin2.level(false);
        pin3.level(false);
        
        pin4.level(false);
        pin5.level(false);
        pin6.level(false);
        pin7.level(false);
        
        hal::delay(clock, 10ms);


        //checking for serial input, saves the  user input as the offset (how to do?)
           
        //hal::print<64>(terminal, "Offset: %f \n", mpu.user_offset);
       

        //mpu.servo_point_up();
    }


}