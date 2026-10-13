/* func_ov003_02219e64 @ 0x02219e64, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02219e64 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_02219e64_2 {
    char pad_00[0x12c];
    struct UnkStruct_02219e64 *p;
};

extern void func_0203ee08(struct UnkStruct_02219e64_2 *, char *);
extern void func_0203e020(struct UnkStruct_02219e64_2 *);

void func_ov003_02219e64(struct UnkStruct_02219e64_2 *self)
{
    if (self->p != 0 && self->p->unk_04 == 0) {
        char *arg = (char *) self;
        if (self) {
            arg += 0xec;
        }
        func_0203ee08(self, arg);
        func_0203e020(self);
    }
}
