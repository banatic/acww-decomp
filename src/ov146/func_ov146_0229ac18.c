/* func_ov146_0229ac18 @ 0x0229ac18, 0x88 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

struct obj_0229ac18 {
    char pad_00[0xb0];
    unsigned char unk_B0;
    char pad_B1[10];
    unsigned char unk_BB;
};

extern int func_ov146_02299670(struct obj_0229ac18 *, int);
extern void func_ov146_02299fbc(struct obj_0229ac18 *);
extern int func_ov146_02299f08(struct obj_0229ac18 *);
extern void func_ov146_02299660(struct obj_0229ac18 *, int);
extern int func_ov146_02299e9c(struct obj_0229ac18 *, int);
extern void func_ov146_02299d04(struct obj_0229ac18 *);
extern void func_ov146_0229a238(struct obj_0229ac18 *);
extern void func_ov146_02299650(struct obj_0229ac18 *, int);
extern void func_ov146_02299684(struct obj_0229ac18 *);
extern void func_ov146_02299e28(struct obj_0229ac18 *);
extern void func_ov002_0220a544(void *);

void func_ov146_0229ac18(struct obj_0229ac18 *self)
{
    if (func_ov146_02299670(self, 0x40) == 0) {
        func_ov146_02299fbc(self);
        if (func_ov146_02299f08(self) != 0) {
            func_ov146_02299660(self, 4);
        }
        if (func_ov146_02299e9c(self, self->unk_BB) != 0) {
            self->unk_B0 = 8;
        } else {
            self->unk_B0 = 9;
        }
    }
    func_ov146_02299d04(self);
    if (func_ov146_02299670(self, 4) != 0) {
        func_ov146_0229a238(self);
        func_ov146_02299650(self, 4);
    }
    func_ov146_02299684(self);
    func_ov146_02299e28(self);
    func_ov002_0220a544((char *) self + 0x1fb4);
}
