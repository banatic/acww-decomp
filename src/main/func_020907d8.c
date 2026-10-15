/* func_020907d8 @ 0x020907d8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090710(void *ptr);
extern void func_020e9fd4(void *);
extern void *data_021d52c8;

void func_020907d8(void *base)
{
    int i;
    void *p;
    void *q;

    for (i = 0; i < 4; i++) {
        func_02090710((char *) base + i * 0x530);
    }

    p = data_021d52c8;
    if (p != 0) {
        func_020e9fd4(p);
        data_021d52c8 = 0;
    }
}
