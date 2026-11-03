/* gatekeeper_talk_lines_3: 3 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_02262738 @ 0x02262738, 0x44 bytes, Thumb
 * func_ov048_022626f0 @ 0x022626f0, 0x48 bytes, Thumb
 * func_ov048_022626a4 @ 0x022626a4, 0x4c bytes, Thumb
 */

struct UnkStruct_022626f0 {
    void *unk_00;
    char pad_04[0xb8];
    char sub_bc;
    char pad_BD[0x333];
    char sub_3f0;
    char pad_3F1[0x113];
    char sub_504;
    char pad_505[0xd3];
    char sub_5d8;
};

extern void *func_020161ac(void *self);
extern char *func_02072dbc(void *sub);
extern int func_0203f674(void *sub);
extern void func_0203f5e0(void *sub);
extern int func_02088274(void *sub);
extern int func_02088264(void *);
extern void func_0203f5dc(void *);
extern int func_0203f664(void *);
extern void *func_02072da4(void *);
extern void *func_0201615c(void *);
extern char data_ov048_02264208[];
extern void func_020edb3c(void *);

void *func_ov048_02262738(void *self)
{
    func_020161ac(self);
    *(void **) self = (void *) ((char *) data_ov048_02264208);
    func_02072dbc((char *) self + 0xbc);
    func_0203f674((char *) self + 0x3f0);
    func_0203f5e0((char *) self + 0x504);
    func_02088274((char *) self + 0x5d8);
    return self;
}

struct UnkStruct_022626f0 *func_ov048_022626f0(struct UnkStruct_022626f0 *self)
{
    self->unk_00 = data_ov048_02264208;
    func_02088264(&self->sub_5d8);
    func_0203f5dc(&self->sub_504);
    func_0203f664(&self->sub_3f0);
    func_02072da4(&self->sub_bc);
    func_0201615c(self);
    return self;
}

void *func_ov048_022626a4(void *self)
{
    *(void **) self = (void *) ((unsigned char *) data_ov048_02264208);
    func_02088264((char *) self + 0x5d8);
    func_0203f5dc((char *) self + 0x504);
    func_0203f664((char *) self + 0x3f0);
    func_02072da4((char *) self + 0xbc);
    func_0201615c(self);
    func_020edb3c(self);
    return self;
}
