#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>



int setch(char chi) {

    write(1, &chi, 1);

    return 1;
}


int setnumber(unsigned int digit) {

    int dimens = 0;

    if(digit > 7 && digit != 0) {

        dimens = dimens + setnumber(digit / 8);
    }

    return (dimens + setch(digit % 8 + '0'));

}


int setdecnumsoct(int digit) {


    int dimens = 0;

    if(digit < 0) {
        dimens = dimens + setch('-');
        digit = digit * (-1);
    }


    if(digit > 9) {
        dimens = dimens + setdecnumsoct(digit / 10);
    }

    return (dimens + setch(digit % 10 + '0'));
}



int setstr(char* str) {

    int dimens = 0;
    

    while(*str) {

        dimens = dimens + setch(*str++);

    }

    return dimens;
}


int setunsigndec(unsigned int digit) {

    int dimens = 0;


    if (digit > 9 && digit != 0) {

        dimens = dimens + setunsigndec(digit / 10);
    }

    return (dimens + setch(digit % 10 + '0'));
}


int sethexdigit(unsigned long int digit) {

    int dimens = 0;

    if(digit > 15) {
        dimens = dimens + sethexdigit(digit / 16);
    }

    if(digit % 16 < 16 && digit % 16 > 9) {


        return (dimens + setch(digit % 16 - 10 + 'A'));

    } else {


        return (dimens + setch(digit % 16 + '0'));
    }
}



int my_printf(char * restrict arrangement, ...) {

    va_list myprog;

    unsigned int undec, unoc;
    
    char *stringchar, character;

    intptr_t hexdec;
    
    int dec, dimens = 0;


    
    va_start(myprog, arrangement);

    while(*arrangement) {
        if(*arrangement == '%') {

            switch(*++arrangement) {

                case 'u':
                    undec = va_arg(myprog, unsigned int);
                    dimens = dimens + setunsigndec(undec);
                    break;


                case 'x':
                    hexdec = va_arg(myprog, intptr_t);
                    dimens = dimens + sethexdigit(hexdec);
                    break;

                
                case 's':
                    stringchar = va_arg(myprog, char*);
                    dimens = dimens + setstr(stringchar);
                    break;

                
                case 'c':
                    character = va_arg(myprog, int);
                    dimens = dimens + setch(character);
                    break;

                
                case 'p':
                    hexdec = va_arg(myprog, intptr_t);
                    dimens = dimens + setstr("0x") + sethexdigit(hexdec);
                    break;

                
                case 'd':
                    dec = va_arg(myprog, int);
                    dimens = dimens + setdecnumsoct(dec);
                    break;


                case 'o':
                    unoc = va_arg(myprog, unsigned int);
                    dimens = dimens + setnumber(unoc);
                    break;


                default:
                dimens = dimens + setch('%');


            }

            arrangement++;
        }


        if(*arrangement != '%') {


            dimens = dimens + setch(*arrangement);

            arrangement++;


        }
    }


    va_end(myprog);

    return dimens;
}


int main() {
    
    my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');

    return 0;
}