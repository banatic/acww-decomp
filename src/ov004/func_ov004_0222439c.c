/* func_ov004_0222439c @ 0x0222439c, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222439c {
    unsigned char b;
};

extern int func_020984e8(void *self);
extern int func_02099670(int a);
extern int func_020a12e8(void);
extern unsigned int func_02088bd4(int s);
extern int func_020644cc(int a);
extern void func_ov004_0222421c(void *self, int a);
extern void func_0206844c(void *ctx, struct UnkStruct_0222439c *t, int a);
extern int data_ov004_02254594;

void func_ov004_0222439c(char *self)
{
    struct UnkStruct_0222439c t;
    int s;
    char *ctx;
    int u;
    unsigned char code;
    int c;

    s = func_02099670(func_020984e8(self));
    ctx = *(char **) (self + 0x40);
    u = data_ov004_02254594;
    code = 0xff;
    if (func_020a12e8() != 0) {
        return;
    }
    c = *(unsigned char *) (self + 0x1e);
    if (c >= 0x1c && c <= 0x23) {
        if (func_02088bd4(s) >= 5 && func_020644cc(3) == 0) {
            code = 0x2c;
        } else {
            *(int *) (ctx + 0x14) = 0;
            func_ov004_0222421c(self, 1);
        }
    }
    c = *(unsigned char *) (self + 0x1e);
    switch (c) {
        case 0x2d:
        case 0x2e:
            if (c == 0x2d) {
                *(char *) (self + 0xb9) = 1;
            }
            *(int *) (ctx + 0x14) = 0;
            func_ov004_0222421c(self, 1);
            break;
    }
    c = *(unsigned char *) (self + 0x1e);
    if (c >= 0x30 && c <= 0x3b) {
        *(int *) (ctx + 0x14) = 0;
        func_ov004_0222421c(self, 3);
    }
    if (code != 0xff) {
        t.b = code;
        func_0206844c(*(char **) (self + 0x40), &t, u);
    }
}
