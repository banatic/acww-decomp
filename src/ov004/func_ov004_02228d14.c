/* func_ov004_02228d14 @ 0x02228d14, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020355e0(void);
extern int func_020e8b0c(int a, int b, int c);
extern char *func_0200420c(void);
extern void func_02056e60(void *p, int a);
extern void func_02054860(void *p);
extern void func_02010f5c(void *self);

void func_ov004_02228d14(char *self)
{
    char *e;
    char *r;
    unsigned char *q;

    if (func_020e8b0c(func_020355e0(), 0x63, 0xab) != 0) {
        e = func_0200420c();
        if (e != 0) {
            if (*(signed char *) (e + 3) != 1) {
                r = self + 0x234;
                q = (unsigned char *) (self + 0x7d4);
                if (q[4] == 0) {
                    q[4] = 1;
                    if (((unsigned int) (*(int *) (r + 0xa4) << 4) >> 16) != 0) {
                        func_02056e60(r + 0xb8, 0xa);
                    }
                }
                *(int *) (r + 0xa4) = 0;
                *(int *) (r + 0xac) = *(int *) (e + 0xc);
                func_02054860(r);
                *(int *) (r + 0xac) = 0x1000;
                *(int *) (self + 0xb0) = 0;
                return;
            }
        }
    }
    func_02010f5c(self);
}
