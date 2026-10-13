/* func_02079fc8 @ 0x02079fc8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(char c);
extern int func_0207a2d8(void *arg0, int arg1, char arg2);
extern void func_020794d4(void *ptr, int arg);
extern void func_02079540(void *ptr, int arg);

void func_02079fc8(void *arg0, char *arg1, int *arg2, void *arg3)
{
    int i;
    char c;
    void *ptr;
    int zero = 0;
    int neg_one = -1;
    int idx = 0;

    for (i = 0; i < 8; i++) {
        c = arg1[idx];
        if (func_0207cf74(c) != 0) {
            if (func_0207a2d8(arg0, *arg2, c) != 0) {
                (*arg2)++;
                ptr = (char *) arg3 + c * 44;
                func_020794d4(ptr, 1);
                func_02079540(ptr, zero);
                *arg1 = neg_one;
            }
        }
        arg1++;
    }
}
