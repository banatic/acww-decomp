/* check_in_gate_8: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222dabc @ 0x0222dabc, 0x1c bytes, Thumb
 * func_ov004_0222daa0 @ 0x0222daa0, 0x1c bytes, Thumb
 * func_ov004_0222da90 @ 0x0222da90, 0x10 bytes, Thumb
 * func_ov004_0222da48 @ 0x0222da48, 0x48 bytes, Thumb
 * func_ov004_0222d9fc @ 0x0222d9fc, 0x4c bytes, Thumb
 * func_ov004_0222d9ac @ 0x0222d9ac, 0x50 bytes, Thumb
 */

typedef struct {
    char pad_00[1];
    unsigned char unk_01;
} UnkStruct_0222daa0;

typedef struct {
    char pad_00[0x2c];
    void *unk_2C;
} UnkStruct_0222daa0_2;

typedef struct {
    UnkStruct_0222daa0 *unk_00;
    UnkStruct_0222daa0_2 *unk_04;
} UnkStruct_0222daa0_3;

struct func_ov003_0221d038_struct {
    char pad_00[0x1c];
    void (*fp)(void *);
    char pad_20[0x70];
    unsigned char unk_90;
};

extern int func_020edf70(unsigned int size);
extern void func_ov004_0222d32c(void *, unsigned char, void *);
extern void *func_020324fc(void *);
extern void func_020565c8(void *);
extern void *func_ov004_0222c87c(void *);
extern void *data_ov004_02254e4c;
extern void *func_020324c4(void *);
extern void *func_020565b0(void *);
extern void *func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);

void *func_ov004_0222da48(char *self);

void func_ov004_0222dabc(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x498)))) {
        func_ov004_0222da48((char *) conditionInput0);
    }
}

void func_ov004_0222daa0(UnkStruct_0222daa0_3 *s)
{
    void *t = s->unk_04->unk_2C;
    if (t != 0) {
        func_ov004_0222d32c(t, s->unk_00->unk_01, s);
    }
}

void func_ov004_0222da90(struct func_ov003_0221d038_struct *obj)
{
    obj->fp = (void (*)(void *)) func_ov004_0222daa0;
    obj->unk_90 = 2;
}

void *func_ov004_0222da48(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    *(void **) (self) = &data_ov004_02254e4c;
    func_020565c8(self + 0x290);
    func_020324fc(self + 0x2bc);
    func_020324fc(self + 0x358);
    func_020324fc(self + 0x3f4);
    return self;
}

void *func_ov004_0222d9fc(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254e4c;
    func_020324c4(self + 0x3f4);
    func_020324c4(self + 0x358);
    func_020324c4(self + 0x2bc);
    func_020565b0(self + 0x290);
    func_ov004_0222c7a0(self);
    return self;
}

void *func_ov004_0222d9ac(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254e4c;
    func_020324c4(self + 0x3f4);
    func_020324c4(self + 0x358);
    func_020324c4(self + 0x2bc);
    func_020565b0(self + 0x290);
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}
