/* func_02070b84 @ 0x02070b84, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(void);

void func_02070b84(void *arg)
{
    unsigned int *p = (unsigned int *) arg;
    if (p[0x1A] != 0) {
        func_020a8fb8();
        p[0x1A] = 0;
    }
}
