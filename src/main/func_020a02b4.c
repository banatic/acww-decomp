/* func_020a02b4 @ 0x020a02b4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d70(int arg);
extern int func_02075978(int arg);
extern int data_020ccf94;

void func_020a02b4(int unused, unsigned char *p, int value)
{
    if (*p == value) {
        if (func_02073d70(data_020ccf94) == 1) {
            *p = value + 1;
        }
    } else if (*p == value + 1) {
        if (func_02075978(value + 1) != 0) {
            *p = value + 2;
        }
    }
}
