/* func_020664e0 @ 0x020664e0, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(unsigned char *);
extern void func_02065eac(int a, int b);
extern void func_02065ef4(int a, int b);

void func_020664e0(int arg)
{
    int result;
    result = func_02065ec0((unsigned char *) arg);
    switch (result) {
        case 1:
            func_02065eac(arg, 2);
            break;
        case 4:
            func_02065eac(arg, 5);
            break;
        default:
            return;
    }
    func_02065ef4(arg, 1);
}
