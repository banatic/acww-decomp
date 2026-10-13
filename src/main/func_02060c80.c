/* func_02060c80 @ 0x02060c80, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060e28(void);

int func_02060c80(int param1, int param2)
{
    int result;
    int temp;
    int mask;
    int shifted;
    int value;
    int *ptr;

    result = func_02060e28();
    if (result != 0) {
        ptr = (int *) (param1 + 0x15a0);
        value = *ptr;
        mask = 0xfffc3fff;
        value &= mask;
        shifted = param2 & 0xf;
        shifted <<= 0xe;
        value |= shifted;
        *ptr = value;
        return 1;
    }
    return 0;
}
