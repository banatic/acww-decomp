/* func_020435a0 @ 0x020435a0, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204482c(void *, int);
extern void *func_02045b5c(void *);
extern int func_02042f20(void *, void *, int, int *, int, int, int, int, int, int);

extern unsigned char data_021c7c48[];

int func_020435a0(void *a, int b)
{
    int ret = -1;
    void *p;
    unsigned short v;
    int buf[2];

    if (func_0204482c(a, 0) == 0) {
        return -1;
    }

    p = func_02045b5c(a);
    if (p != 0) {
        v = *(unsigned short *) p;
        buf[0] = v >> 8;
        buf[1] = v & 0xff;
        ret = func_02042f20((void *) data_021c7c48, a, 0x11, buf, b, b, 0, 0, 0, -1);
    }
    return ret;
}
