/* func_02098be8 @ 0x02098be8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_02098f48(void *a, int b);
extern int func_02098c2c(void *a, int b);

int func_02098be8(void *arg)
{
    unsigned short *p = func_02098f48(arg, 0);
    int i = 0;
    int found = ~0;

    while (i < 15) {
        if (*p == 0xFFF1) {
            found = i;
            break;
        }
        p++;
        i++;
    }

    if (found == ~0) {
        found = func_02098c2c(arg, 0);
    }
    return found;
}