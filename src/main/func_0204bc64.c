/* func_0204bc64 @ 0x0204bc64, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(unsigned short *);

int func_0204bc64(unsigned short *argument0)
{
    int result;
    result = func_0204b42c((unsigned short *) argument0);
    result -= 0x3000;
    return result >> 2;
}
