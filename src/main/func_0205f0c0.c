/* func_0205f0c0 @ 0x0205f0c0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ec4(void *);
extern void func_020ba004(void *);

void func_0205f0c0(void *base, int idx)
{
    unsigned int flag;
    int off;

    off = idx * 28;
    flag = (((unsigned char *) base + off)[0x19d] == 1) ? 1 : 0;
    if (flag > 0) {
        func_020b9ec4((unsigned char *) base + 0x190 + off);
    } else {
        func_020ba004((unsigned char *) base + 0x190 + off);
    }
}
