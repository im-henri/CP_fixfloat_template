// Demo of using libfixmath on Classpads SH4
// https://github.com/PetteriAimonen/libfixmath/tree/master/libfixmath
// Note that not all of the source is included. If you need other functionaly
// then put the libfixmath source under "src/Fixmath"
#include "libfixmath/fix16.hpp"
//
#include "app_description.hpp"
#include <sdk/calc/calc.hpp>
#include <sdk/os/lcd.hpp>
#include <sdk/os/debug.hpp>

#define SCREEN_X 320
#define SCREEN_Y 528

void draw_center_square(int16_t cx, int16_t cy, int16_t sx, int16_t sy, uint16_t color)
{
    for(int16_t i=-sx/2; i<sx/2; i++)
    {
        for(int16_t j=-sy/2; j<sy/2; j++)
        {
            setPixel(cx+i, cy+j, color);
        }
    }
}

extern "C"
void main()
{
    calcInit(); //backup screen and init some variables

    // Constants such as PI or e are available
    Fix16 angle = -fix16_pi;
    Fix16 hue   = 0.0f;
    while(true){
        // ------ Clear screen ------
        fillScreen(color(255, 255, 255));

        // ----- Check for exit -----
        uint32_t k1,k2;
        getKey(&k1,&k2);
        if(testKey(k1,k2,KEY_CLEAR))
            break;

        // ------ Fix16 example ------
        // Supports math with float
        angle += 0.10f;
        hue   += 0.02f;
        // Trigonometric functions
        auto sin_angle = angle.sin();
        auto cos_angle = angle.cos();
        // Fix16 casted to int16_t
        int16_t x = (sin_angle * 40.0f);
        int16_t y = (cos_angle * 40.0f);
        // Coloring r
        int16_t hue_r = (int16_t) ((hue.sin() + 1.0f)/2.0f * 255.0f);
        int16_t hue_b = (int16_t) ((hue.cos() + 1.0f)/2.0f * 255.0f);
        uint8_t col_r = hue_r;
        uint8_t col_g = 0;
        uint8_t col_b = hue_b;
        draw_center_square(SCREEN_X/2 + x, SCREEN_Y/2 + y, 30, 30, color(col_r,col_g,col_b));
        // Debug printing
        char buff[14];
        fix16_to_str(sin_angle, buff, 3);
        Debug_Printf(2, 2, false, 0, "sin(angle)=%s", buff);
        fix16_to_str(cos_angle, buff, 3);
        Debug_Printf(2, 3, false, 0, "cos(angle)=%s", buff);

        // ----- Refresh screen -----
        LCD_Refresh();
    }

    calcEnd(); //restore screen and do stuff
}
