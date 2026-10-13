/* func_0209761c @ 0x0209761c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern int data_020d18d0[];
extern unsigned char *data_020e3048[];

unsigned char func_0209761c(unsigned int param)
{
    unsigned int index;
    if (param <= 2 || param == 12) {
        index = 3;
    } else if (param <= 5) {
        index = 0;
    } else if (param <= 8) {
        index = 1;
    } else {
        index = 2;
    }
    return data_020e3048[index][func_020644cc(data_020d18d0[index])];
}
