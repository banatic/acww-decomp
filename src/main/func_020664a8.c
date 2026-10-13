/* func_020664a8 @ 0x020664a8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(void *arg);
extern void func_02065eac(void *arg, int value);

void func_020664a8(void *arg)
{
    int result;

    result = func_02065ec0(arg);
    switch (result) {
        case 2:
            func_02065eac(arg, 3);
            break;
        case 5:
            func_02065eac(arg, 6);
            break;
        case 7:
            func_02065eac(arg, 8);
            break;
        default:
            break;
    }
}
