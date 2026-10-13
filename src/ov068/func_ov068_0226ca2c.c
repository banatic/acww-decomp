/* func_ov068_0226ca2c @ 0x0226ca2c, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02013894(const void *);
extern int func_020644cc(int);
extern int func_02013300(const void *);
extern int data_ov068_022767ac[];

int func_ov068_0226ca2c(void *p)
{
    int idx, val, nxt;

    idx = func_020644cc(func_02013894((char *) p + 0x3c) ? 2 : 3);
    val = data_ov068_022767ac[idx];
    if (val == func_02013300((char *) p + 0x3c)) {
        nxt = idx + 1 < 3 ? idx + 1 : 0;
        val = data_ov068_022767ac[nxt];
    }
    return val;
}
