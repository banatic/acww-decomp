/* func_ov004_0221c2a4 @ 0x0221c2a4, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020961a8(int k);
extern int func_0201c314(void *self, void *p);
extern void func_020147fc(void *p, int x, int y, int z);

int func_ov004_0221c2a4(void *self)
{
    void *p = func_020961a8(4);
    if (p != 0) {
        func_020147fc((char *) self + 0x618, 0, func_0201c314(self, p), 0);
        return 1;
    }
    return 0;
}
