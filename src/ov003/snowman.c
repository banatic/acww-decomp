/* snowman: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02219e98 @ 0x02219e98, 0x24 bytes, Thumb
 * func_ov003_02219e94 @ 0x02219e94, 0x4 bytes, Thumb
 * func_ov003_02219e64 @ 0x02219e64, 0x30 bytes, Thumb
 */

struct UnkStruct_02219e98 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_02219e98_2 {
    char pad_00[0x12c];
    struct UnkStruct_02219e98 *ptr;
};

struct UnkStruct_02219e64 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_02219e64_2 {
    char pad_00[0x12c];
    struct UnkStruct_02219e64 *p;
};

extern int func_ov003_0221a004(void *obj, int arg);
extern void func_0203ee08(struct UnkStruct_02219e64_2 *, char *);
extern int func_0203e020(struct UnkStruct_02219e64_2 *);

void func_ov003_02219e98(struct UnkStruct_02219e98_2 *obj)
{
    if (obj->ptr != 0 && obj->ptr->unk_04 != 0) {
        func_ov003_0221a004(obj, 2);
    }
}

int func_ov003_02219e94(void)
{
    return 1;
}

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
