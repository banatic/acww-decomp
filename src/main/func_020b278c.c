/* func_020b278c @ 0x020b278c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b27d4(int diff);

int func_020b278c(int r0)
{
    unsigned short store;
    int flag;
    unsigned int v;
    int diff;
    store = (unsigned short) r0;
    flag = 0;
    v = *(volatile unsigned short *) &store;
    if (v >= 0x5001 && v <= 0x5008) {
        flag = 1;
    }
    if (flag == 0) {
        goto fail;
    }
    if (v >= 0x5001 && v <= 0x5008) {
        diff = v - 0x5001;
    } else {
        diff = ~0;
    }
    return func_020b27d4(diff);
fail:
    return 0;
}
