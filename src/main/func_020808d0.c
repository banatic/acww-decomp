/* func_020808d0 @ 0x020808d0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020808ec(unsigned int);
extern unsigned char data_020cd4dc[];

unsigned char func_020808d0(unsigned int object)
{
    unsigned char result;
    unsigned int index;

    index = func_020808ec(object);
    if (index >= 0x21) {
        index = 0;
    }
    result = data_020cd4dc[index];
    return result;
}
