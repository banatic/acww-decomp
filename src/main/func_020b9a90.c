/* func_020b9a90 @ 0x020b9a90, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b9c7c(void *p);
extern unsigned int func_020ba0dc(void *p);
extern void func_020ba07c(void *p);

int func_020b9a90(void *p)
{
    unsigned char *q = (unsigned char *) p;

    if (func_020b9c7c(p) != 0) {
        return 1;
    }

    switch (q[0xe]) {
        case 8:
            func_020ba0dc(q + 0x10);
            q += 0x24;
            func_020ba0dc(q);
            goto success;
        case 9:
            func_020ba0dc(q + 0x10);
            q += 0x24;
            func_020ba07c(q);
            goto success;
        default:
            return 0;
    }

success:
    return 1;
}
