
#include <libhal-arm-mcu/stm32f1/output_pin.hpp>
#include <libhal-soft/bit_bang_i2c.hpp> 
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>
#include <libhal/output_pin.hpp>
#include <libhal/units.hpp>
#include <libhal-micromod/micromod.hpp>

#include <libhal-stm32f1/output_pin.hpp>
#include <libhal-stm32f1/input_pin.hpp>


#include "../include/mpu6050.hpp"
#include "../hardware_map.hpp"

using namespace hal::literals;
using namespace std::chrono_literals;

void application(application_framework &p_framework){
    //auto& i2c2 = *p_framework.i2c;
    auto& clock = *p_framework.steady_clock;
    auto& terminal = *p_framework.terminal;
    // auto& scl = *p_framework.scl; 
    // auto& sda = *p_framework.sda; 
    auto pin0 = hal::stm32f1::output_pin('A', 0); // work
    //auto pin1 = hal::stm32f1::output_pin('A',15);
    //auto pin2 = hal::stm32f1::output_pin('B', 3);
    //auto pin3 = hal::stm32f1::output_pin('B', 4);
    auto pin4 = hal::stm32f1::output_pin('B', 12); // work
    //auto pin5 = hal::stm32f1::output_pin('B',13); // work
    //auto pin6 = hal::stm32f1::output_pin('B', 14); // work  
    //auto pin7 = hal::stm32f1::output_pin('B', 15);
    // auto pin0_i = hal::stm32f1::input_pin('A', 0); // work
    // auto pin4_i = hal::stm32f1::input_pin('B', 12); // work

    // pin0.configure({ .resistor = hal::pin_resistor::pull_up, .open_drain = true });
    // pin4.configure({ .resistor = hal::pin_resistor::pull_up, .open_drain = true });



    pin0.level(true);
    pin4.level(true);
    *((unsigned int*) (0x40010800 + 0x00)) = 0xAAAAAAAA; 



    // 0x88888888 0b10001000100010001000100010001000
    // 0xAAAAAAAA 0b10101010101010101010101010101010
    // 0xAAAAAAAA 0b01010101010101010101010101010101

    // pin0_i.configure({ .resistor = hal::pin_resistor::pull_up,  });
    // pin4_i.configure({ .resistor = hal::pin_resistor::pull_up,  });
    // hal::delay(clock, 1s);
    hal::soft::bit_bang_i2c bit_bang_i2c({ .sda = &pin0, .scl = &pin4 }, clock);
  bit_bang_i2c.configure(hal::i2c::settings{ .clock_rate = 100.0_kHz });
    // pin0.
    hal::delay(clock, 50ms);
    auto mpu=mpu6050(bit_bang_i2c,clock,terminal);
    hal::print(terminal, "mpu initialized");
    while(true){
         mpu.read_xy();
        //prints on the serial monitor
         hal::print<64>(terminal, "Y= %f degrees", mpu.Y_out);
         hal::print<64>(terminal, "X = %f degrees", mpu.X_out);

        //checking for serial input, saves the  user input as the offset (how to do?)
           
        hal::print<64>(terminal, "Offset: %f \n", mpu.user_offset);
       

        //mpu.servo_point_up();
    }


}