/* func_ov004_022316f4 @ 0x022316f4, 0x100 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

// Preserve the ROM register reuse and instruction scheduling.
#pragma opt_propagation off
typedef struct {
    int x, y, z;
} Vec;
extern unsigned char *data_ov004_022588c8;
extern Vec data_ov004_022478d0;
extern unsigned char data_ov004_022559ec[], data_ov004_02255a08[], data_021dc7a8[];
extern void *data_021c9b24;
extern void func_0203efb0(void *, int);
extern int func_ov004_0222c600(void *, void *, void *);
extern void *func_ov004_0222c3c4(void *, int);
extern int func_02055140(void *, void *);
extern void func_02055060(void *, void *, int, int, unsigned short, unsigned short);
extern void func_02055050(void *);
extern void *func_020b6590(void);
extern int func_020b7dc8(void *, void *, Vec *, int, int, int, short, int, unsigned char);
extern unsigned char func_020b65c4(void);
extern int func_0209f150(void *, int);
extern void func_ov004_0223121c(void *, int);
extern void func_0209f128(void *, int);
int func_ov004_022316f4(unsigned char *self)
{
    Vec position;
    unsigned char *flags;
    int x, y, z;
    data_ov004_022588c8 = self;
    x = data_ov004_022478d0.x;
    *(int *) (self + 0x5c) = x;
    y = data_ov004_022478d0.y;
    *(int *) (self + 0x60) = y;
    z = data_ov004_022478d0.z;
    *(int *) (self + 0x64) = z;
    func_0203efb0(self, 0);
    func_ov004_0222c600(self, data_ov004_022559ec, data_ov004_02255a08);
    if (func_ov004_0222c3c4(self + 0x1a4, 0) && func_02055140(self + 0xec, data_021c9b24)) {
        func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0), 3, 0x1000, 0, 0);
        func_02055050(self + 0xec);
    }
    position.x = x;
    position.y = y;
    position.z = z;
    func_020b7dc8(func_020b6590(), self + 0x374, &position, 0x2000, 0x2000, 0x2000, 0, 13, 255);
    flags = data_021dc7a8;
    if (func_020b65c4() == 6) {
        if (!func_0209f150(flags, 0)) {
            func_ov004_0223121c(self, 8);
            func_0209f128(flags, 0);
        } else {
            func_ov004_0223121c(self, 7);
        }
    } else {
        func_ov004_0223121c(self, 0);
    }
    return 1;
}
