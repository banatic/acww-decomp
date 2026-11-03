/* walrus: 2 functions, module ov079
 * mwccarm 1.2/base -O4,s
 * func_ov079_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov079_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
 */

struct UnkStruct_02278a28 {
    int *unk_00;
    char pad_04[0x654];
    int unk_658;
};

extern void *func_ov079_02278d1c(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern char data_ov079_0227a104[];

struct UnkStruct_02278a28 *func_ov079_02278a28(struct UnkStruct_02278a28 *self)
{
    self->unk_00 = ((int *) data_ov079_0227a104);
    func_ov079_02278d1c((void *) &self->unk_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}

void *func_ov079_02278a00(void *self)
{
    *(void **) self = data_ov079_0227a104;
    func_ov079_02278d1c((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
