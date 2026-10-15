/* func_ov004_0221e8b8 @ 0x0221e8b8, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int gt2GetIncomingBufferSize(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);

int func_ov004_0221e8b8(int a0, void *self)
{
    int r1 = gt2GetIncomingBufferSize((char *) self + 0x680);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}
