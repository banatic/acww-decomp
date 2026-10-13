/* func_ov004_02228c18 @ 0x02228c18, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern char *data_020ccf94;
extern void func_ov004_0223a6d8(void *p);
extern void func_ov004_02228d14(void *self);
extern void func_02010ca4(void *self);
extern int func_02073908(char *a, int b);
extern void func_ov004_02228c84(void *self);
extern int func_02008258(void *self, int a);

void func_ov004_02228c18(char *self)
{
    unsigned int t;

    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t != 0) {
        func_ov004_0223a6d8(self + 0x5c);
    }
    func_ov004_02228d14(self);
    func_02010ca4(self);
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_ov004_02228c84(self);
    } else {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
    }
}
