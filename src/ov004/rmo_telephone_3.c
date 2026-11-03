/* rmo_telephone_3: 10 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022310f4 @ 0x022310f4, 0x24 bytes, Thumb
 * func_ov004_022310f0 @ 0x022310f0, 0x2 bytes, Thumb
 * func_ov004_022310cc @ 0x022310cc, 0x24 bytes, Thumb
 * func_ov004_022310c8 @ 0x022310c8, 0x2 bytes, Thumb
 * func_ov004_022310a4 @ 0x022310a4, 0x24 bytes, Thumb
 * func_ov004_02231084 @ 0x02231084, 0x20 bytes, Thumb
 * func_ov004_02231048 @ 0x02231048, 0x3c bytes, Thumb
 * func_ov004_02231044 @ 0x02231044, 0x2 bytes, Thumb
 * func_ov004_02231040 @ 0x02231040, 0x2 bytes, Thumb
 * func_ov004_0223103c @ 0x0223103c, 0x2 bytes, Thumb
 */

struct UnkStruct_022310f4;

struct UnkStruct_022310f4_2;

struct UnkStruct_022310f4 {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_022310f4_2 {
    char pad_00[720];
    struct UnkStruct_022310f4 *b;
};

extern void func_ov004_0223121c(void *self, int k);
extern int func_ov004_0222bed8(void);
extern int func_ov004_0222c2dc(void *, int);
extern int func_02056f94(void *p);
extern void func_0203ee08(void *self, void *a);
extern int func_0203e020(void *self);

void func_ov004_022310f4(struct UnkStruct_022310f4_2 *self)
{
    struct UnkStruct_022310f4 *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_0223121c((void *) self, 3);
        }
    }
}

void func_ov004_022310f0(void) {}

void func_ov004_022310cc(void *self)
{
    void *p = *(void **) ((char *) self + 0x2d0);
    if (p != 0 && *(void **) ((char *) p + 4) == 0) {
        func_ov004_0223121c(self, 0x5);
    }
}

void func_ov004_022310c8(void) {}

void func_ov004_022310a4(void *self)
{
    void *p = *(void **) ((char *) self + 0x2d0);
    if (p != 0 && *(void **) ((char *) p + 4) == 0) {
        func_ov004_0223121c(self, 0x5);
    }
}

int func_ov004_02231084(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222bed8();
    return func_ov004_0222c2dc(self + 0x250, 0x4d5);
}

void func_ov004_02231048(unsigned char *self)
{
    unsigned char *a;
    if (func_02056f94(self + 0x188) != 0) {
        a = self;
        if (self != 0) {
            a = self + 0x290;
        }
        func_0203ee08(self, a);
        func_0203e020(self);
        func_ov004_0223121c(self, 6);
    }
}

void func_ov004_02231044(void) {}

void func_ov004_02231040(void) {}

void func_ov004_0223103c(void) {}
