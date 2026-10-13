/* func_ov004_02221198 @ 0x02221198, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02220318(void *self);
extern int func_ov004_02220210(void *self);
extern int func_020ea990(void *a, void *b);
extern void func_0201b458(void *buf, void *self, void *p);
extern int func_0200322c(void *a, void *b);
extern int func_020e8b4c(int a, int b);
extern int func_020eaa2c(void *buf, void *p);
extern void func_ov004_02221550(void *self, int k);

int func_ov004_02221198(void *self)
{
    char buf[0x10];
    int d, e;

    if (func_ov004_02220318(self) != 0) {
        return 1;
    }
    if (*((unsigned char *) self + 0xac8) != 2) {
        return 1;
    }
    if (func_ov004_02220210(self) != 0) {
        d = func_020ea990((char *) self + 0x5c, (char *) self + 0x89c);
        func_0201b458(buf, self, (char *) self + 0x89c);
        e = func_020e8b4c(*(short *) ((char *) self + 0x8e), func_0200322c((char *) self + 0x5c, (char *) self + 0x89c));
        if (d > *(int *) ((char *) self + 0xad8) && func_020eaa2c(buf, (char *) self + 0x5c) != 0) {
            func_ov004_02221550(self, 5);
        } else if (e > 0x2000) {
            func_ov004_02221550(self, 4);
        }
    }
    return 1;
}
