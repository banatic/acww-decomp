/* func_02090000 @ 0x02090000, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(unsigned char *);

int func_02090000(unsigned char *argument0)
{
    int result;
    if (func_02065ec0((unsigned char *) argument0) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
