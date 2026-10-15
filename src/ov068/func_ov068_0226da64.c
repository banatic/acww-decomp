/* func_ov068_0226da64 @ 0x0226da64, 0x58 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
extern void *func_0202e8e4(void *p);
extern void func_ov068_02266cf0(void *p);
extern void *func_ov068_0226ce5c(void *p);
extern void *func_0201259c(void *p);
extern void func_ov068_02266f40(void *p);
extern char data_ov068_022771c0;

void *func_ov068_0226da64(void)
{
    void *p;
    p = func_020edf70(0xa10);
    if (p != 0) {
        func_0202e8e4(p);
        *(void **) p = (void *) &data_ov068_022771c0;
        func_ov068_02266cf0((char *) p + 0x898);
        func_ov068_0226ce5c((char *) p + 0x8b8);
        func_0201259c((char *) p + 0x9b4);
        func_ov068_02266f40((char *) p + 0x9f4);
    }
    return p;
}
