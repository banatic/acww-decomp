/* func_02098e10 @ 0x02098e10, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098e44(int arg1, int arg2);
extern int func_02065ec0(void *p);

int func_02098e10(int arg)
{
    unsigned char *p;
    int i;
    p = (unsigned char *) func_02098e44(arg, 0);
    for (i = 0; i < 10; i++) {
        if (func_02065ec0(p) == 0) {
            return i;
        }
        p += 0x100;
    }
    return -1;
}
