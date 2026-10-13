/* func_0206e808 @ 0x0206e808, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9898(void *ptr);

void func_0206e808(void *arg)
{
    unsigned int *p = (unsigned int *) arg;
    unsigned int zero = 0;
    unsigned int neg_one = 0xFFFFFFFF;

    p[0] = zero;
    p[5] = neg_one;
    p[3] = zero;
    p[2] = zero;

    if (p[4] != 0) {
        func_020e9898((void *) p[4]);
        p[4] = 0;
    }

    if (p[6] != 0) {
        func_020e9898((void *) p[6]);
        p[6] = 0;
    }
}
