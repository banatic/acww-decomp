/* func_ov047_022606f0 @ 0x022606f0, 0x32 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void *);
extern int func_02099020(int, int);

void func_ov047_022606f0(void *arg0, int arg1)
{
    if (arg1 == 0) {
        if (func_02099020(func_020984e8(arg0), 0x35) == 0) {
            *(int *) ((char *) arg0 + 0xd0) = 0x4b;
        } else {
            *(int *) ((char *) arg0 + 0xd0) = 0x19;
        }
    } else {
        *(int *) ((char *) arg0 + 0xd0) = 0x15;
    }
}
