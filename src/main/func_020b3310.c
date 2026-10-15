/* func_020b3310 @ 0x020b3310, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b3658(int *);

int func_020b3310(int *argument0)
{
    int result;
    if (func_020b3658((int *) argument0) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
