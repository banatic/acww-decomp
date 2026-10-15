/* func_0204bcb4 @ 0x0204bcb4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(unsigned short *);

int func_0204bcb4(unsigned short *argument0)
{
    int result;
    int value;

    value = func_0204b42c((unsigned short *) argument0);
    if (value == 0x0000f031) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
