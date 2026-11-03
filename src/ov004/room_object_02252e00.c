/* room_object_02252e00: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02219f28 @ 0x02219f28, 0x30 bytes, Thumb
 * func_ov004_02219f00 @ 0x02219f00, 0x28 bytes, Thumb
 * func_ov004_02219ed8 @ 0x02219ed8, 0x28 bytes, Thumb
 * func_ov004_02219e54 @ 0x02219e54, 0x84 bytes, Thumb
 */

extern void func_ov004_02210054(void *self, int a, int b, int c);
extern int func_ov004_0220fde0(void *self);
extern int func_ov004_02210744(void *self);
extern int func_ov004_0220d2a8(void *p);
extern int func_0205265c(void *p, int a, int b, int c);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern int func_ov004_0221078c(void *);
extern void func_ov004_0220d290(unsigned char *self, int pending);
extern int func_ov004_0220ffbc(void *self);
extern int func_ov004_022107d4(void *self);
extern int func_02056f28(void *p, int a);

int func_ov004_02219f28(void *self)
{
    func_ov004_02210054(self, 0, 1, 0x1000);
    if (func_ov004_0220fde0(self) != 0x207) {
        func_ov004_02210744(self);
    }
    return 1;
}

void func_ov004_02219f00(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740)) {
        func_0205265c(self, 1, 0xff, 1);
    }
}

int func_ov004_02219ed8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022101e4(self, 0x0, 0x1, 0x1000, 0x0);
    func_ov004_0221078c(self);
    return 0x1;
}

void func_ov004_02219e54(char *self)
{
    int r = func_ov004_0220fde0(self);
    switch (r) {
        case 0xb9:
        case 0xba:
            if (func_ov004_0220d2a8(self + 0x740) != 0) {
                func_0205265c(self, 1, 0xff, 1);
                return;
            }
            break;
    }
    func_ov004_0220d290((unsigned char *) self + 0x740, 0);
    if (func_ov004_0220ffbc(self) != 0) {
        func_0205265c(self, 0, 0xff, 1);
    } else {
        func_ov004_022107d4(self);
    }
    if (func_ov004_0220fde0(self) == 0x207) {
        if (func_02056f28(self + 0x5d4, 0x30) != 0) {
            func_ov004_02210744(self);
        }
    }
}
