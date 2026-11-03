/* wfc_host_list_2: 4 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_0229ac18 @ 0x0229ac18, 0x88 bytes, Thumb
 * func_ov146_0229abe0 @ 0x0229abe0, 0x38 bytes, Thumb
 * func_ov146_0229ab28 @ 0x0229ab28, 0xb8 bytes, Thumb
 * func_ov146_0229aac8 @ 0x0229aac8, 0x60 bytes, Thumb
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
extern int func_ov146_02299d04(struct obj_0229ac18 *);
extern void func_ov146_0229a238(struct obj_0229ac18 *);
extern void func_ov146_02299650(struct obj_0229ac18 *, int);
extern void func_ov146_02299684(struct obj_0229ac18 *);
extern void func_ov146_02299e28(struct obj_0229ac18 *);
extern void func_ov002_0220a544(void *);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void *data_021fbe94;
extern unsigned char data_ov146_0229b71c[];
extern unsigned char data_ov146_0229b72c[];
extern unsigned char data_ov146_0229b73c[];
extern unsigned char data_ov146_0229b750[];
extern unsigned char data_ov146_0229b764[];
extern int func_02002c6c(void *, void *, int, int, int, int);
extern int func_02002d14(void *, void *, int, int, int, int);
extern int func_02064af4(void *, void *, int);
extern void MIi_CpuCopy16(void *, void *, int);
extern int func_02002ca4(void *, void *, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern unsigned char data_ov146_0229b6e0[];
extern unsigned char data_ov146_0229b6f4[];
extern unsigned char data_ov146_0229b708[];

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

void func_ov146_0229abe0(void)
{
    func_02001c08(0);
    func_020029e8(6, 1);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
}

void func_ov146_0229ab28(unsigned char *base)
{
    void *p = data_021fbe94;
    func_02002c6c(data_ov146_0229b71c, p, 6, 0x11, 0x11, 0x5c);
    func_02002d14(data_ov146_0229b72c, p, 6, 1, 1, 8);
    func_02064af4(data_ov146_0229b73c, base + 0x158a, 0x20);
    MIi_CpuCopy16(base + 0x158a, base + 0x15aa, 0x20);
    func_02002ca4(data_ov146_0229b750, p, 6);
    func_02064af4(data_ov146_0229b764, base + 0x58a, 0x800);
    func_0206fdd4(base + 0x58a, 5, 7, 0xe, 0x14, 7);
    func_0206fdd4(base + 0x58a, 0x10, 7, 0x17, 0x14, 7);
}

void func_ov146_0229aac8(void *receiver)
{
    void *obj = data_021fbe94;
    func_02002c6c((void *) data_ov146_0229b6e0, obj, 8, 0x80, 0x80, 0xff);
    func_02002c6c((void *) data_ov146_0229b6f4, obj, 8, 0x160, 0x160, 0x1ff);
    func_02002d14((void *) data_ov146_0229b708, obj, 8, 4, 4, 0xd);
}
