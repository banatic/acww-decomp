/* func_ov004_02225670 @ 0x02225670, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef void (*VF)(void *);

extern int func_0201c2a4(void *self, int a);
extern void func_02016108(void *p, int n);
extern int gt2GetIncomingBufferSize(void *p);
extern int func_0201c314(void *self, int n);
extern int func_020147fc(void *p, int a, int b, int c);

int func_ov004_02225670(char *self)
{
    int n;
    int r;

    (*(VF **) (self + 0x658))[2](self + 0x658);
    func_02016108(self + 0x658, func_0201c2a4(self, 4));
    n = gt2GetIncomingBufferSize(self + 0x658);
    r = 0;
    if (n != 0) {
        r = func_0201c314(self, n);
    }
    func_020147fc(self + 0x618, 0, r, 0);
    return 1;
}
