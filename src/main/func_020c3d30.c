/* func_020c3d30 @ 0x020c3d30, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int gt2GetIncomingBufferSize(void *p);
extern int func_0201c314(void *self, int flag);
extern void func_020147fc(void *p1, int a, int b, int c);
extern void func_020c3c18(void *p, int a);

int func_020c3d30(char *self)
{
    int r1 = gt2GetIncomingBufferSize(self + 0x658);
    int r2 = 0;

    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc(self + 0x618, 0, r2, 0);
    func_020c3c18(self + 0x658, 0);
    return 1;
}
