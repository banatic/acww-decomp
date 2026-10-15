/* func_ov068_02271ee4 @ 0x02271ee4, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_02008258(void *, int);
extern int func_0200c3b0(void *, int, int, int);
extern unsigned char *func_0209626c(void);

void func_ov068_02271ee4(void *self)
{
    unsigned char *flag;
    if (func_02056f94((char *) self + 0x2d0)) {
        *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
        func_0200c3b0(self, 0, 5, -1);
        flag = func_0209626c();
        *flag = 0;
    }
}
