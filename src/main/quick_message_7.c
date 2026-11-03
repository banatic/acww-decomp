/* quick_message_7: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203a2b8 @ 0x0203a2b8, 0x4 bytes, Thumb
 * func_0203a2b4 @ 0x0203a2b4, 0x4 bytes, Thumb
 * func_0203a23c @ 0x0203a23c, 0x78 bytes, Thumb
 * func_0203a1f8 @ 0x0203a1f8, 0x44 bytes, Thumb
 * func_0203a1ac @ 0x0203a1ac, 0x4c bytes, Thumb
 * func_0203a054 @ 0x0203a054, 0x158 bytes, Thumb
 */

typedef struct UnkStruct_0203a054 {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
    unsigned char pad_14[0x48 - 0x14];
    int unk_48;
    int unk_4C;
    int unk_50;
    unsigned char pad_54[0xb4 - 0x54];
    unsigned char unk_B4;
} UnkStruct_0203a054;

extern void func_0208af30(void *);
extern void func_0208a1f8(void *);
extern void *func_0203a404(void *);
extern void *func_0203a344(void *);
extern unsigned char data_020da658[];
extern void func_020399c8(void *);
extern void func_0203990c(void *);
extern void func_0203a330(void *);
extern void *func_0203a3ec(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *self);
extern int func_0208a1d0(void *p);
extern int func_0208aef0(UnkStruct_0203a054 *s);
extern int func_0208a1b0(void *p, int n);
extern int func_0208aeec(UnkStruct_0203a054 *s);
extern int func_0208a198(void *p, int n);
extern void func_02088df8(int a0, int a1, int a2, int a3, int s1, int s2, int s3, int s4, int s5, int s6, int s7, int s8);

int func_0203a2b8(int *p0)
{
    return p0[2];
}

int func_0203a2b4(int *p0)
{
    return p0[1];
}

void *func_0203a23c(void *self)
{
    void *p;

    func_0208af30(self);
    ((unsigned int *) self)[0] = (unsigned int) (unsigned int) data_020da658;
    ((unsigned int *) self)[3] = 0;
    ((unsigned int *) self)[4] = 0;
    ((unsigned int *) self)[5] = 0;
    ((unsigned int *) self)[6] = 0;

    p = self;
    p = (char *) p + 0x1c;
    func_0208a1f8(p);

    p = self;
    p = (char *) p + 0x30;
    func_0208a1f8(p);

    ((unsigned int *) self)[0x11] = 0;
    ((unsigned int *) self)[0x12] = 0;
    ((unsigned int *) self)[0x13] = 0;
    ((unsigned int *) self)[0x14] = 0;

    p = self;
    p = (char *) p + 0x54;
    func_0203a404(p);

    p = self;
    p = (char *) p + 0x88;
    func_0203a344(p);

    ((unsigned int *) self)[0x27] = 0;
    ((unsigned int *) self)[0x28] = 0;
    ((unsigned int *) self)[0x29] = 0;
    ((unsigned int *) self)[0x2a] = 0;
    ((unsigned int *) self)[0x2b] = 0;
    ((unsigned int *) self)[0x2c] = 0;
    ((unsigned char *) self)[0xb4] = 0;

    return self;
}

void *func_0203a1f8(void *p)
{
    *(void **) p = (void *) ((char *) data_020da658);
    func_020399c8(p);
    func_0203990c(p);
    func_0203a330((char *) p + 0x88);
    func_0203a3ec((char *) p + 0x54);
    func_0208a1f4((char *) p + 0x30);
    func_0208a1f4((char *) p + 0x1c);
    func_0208af00(p);
    return p;
}

void *func_0203a1ac(void *self)
{
    *(void **) self = (void *) ((int *) data_020da658);
    func_020399c8(self);
    func_0203990c(self);
    func_0203a330((char *) self + 0x88);
    func_0203a3ec((char *) self + 0x54);
    func_0208a1f4((char *) self + 0x30);
    func_0208a1f4((char *) self + 0x1c);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}

void func_0203a054(UnkStruct_0203a054 *self)
{
    int a, b, s;
    int a2, b2, s2;

    if (self->unk_B4 == 0) {
        return;
    }
    if (self->unk_0C == 0) {
        a = func_0208a1d0((char *) self + 0x30);
        b = func_0208aef0(self) + func_0208a1b0((char *) self + 0x30, -1);
        s = self->unk_50 + (self->unk_4C + (self->unk_48 + func_0208aeec(self)) + func_0208a198((char *) self + 0x30, -1));
        func_02088df8(0, a, b, s, self->unk_10, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    } else {
        a = func_0208a1d0((char *) self + 0x1c);
        b = func_0208aef0(self) + func_0208a1b0((char *) self + 0x1c, -1);
        s = self->unk_50 + (self->unk_4C + (self->unk_48 + func_0208aeec(self)) + func_0208a198((char *) self + 0x1c, -1));
        a2 = func_0208a1d0((char *) self + 0x30);
        b2 = func_0208aef0(self) + func_0208a1b0((char *) self + 0x30, -1);
        s2 = self->unk_50 + (self->unk_4C + (self->unk_48 + func_0208aeec(self)) + func_0208a198((char *) self + 0x30, -1));
        func_02088df8(2, a, b, s, self->unk_10, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        func_02088df8(2, a2, b2, s2, self->unk_10, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}
