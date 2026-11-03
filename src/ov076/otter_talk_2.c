/* otter_talk_2: 4 functions, module ov076
 * mwccarm 1.2/base -O4,s
 * func_ov076_02278e90 @ 0x02278e90, 0x24 bytes, Thumb
 * func_ov076_02278e78 @ 0x02278e78, 0x18 bytes, Thumb
 * func_ov076_02278e58 @ 0x02278e58, 0x20 bytes, Thumb
 * func_ov076_02278e34 @ 0x02278e34, 0x24 bytes, Thumb
 */

struct UnkStruct_02278e90 {
    void *unk_00;
    char pad_04[0xB4];
    unsigned short unk_B8;
};

typedef struct {
    void *unk_00;
} UnkStruct_02278e78;

struct Pair {
    unsigned int a;
    unsigned int b;
};

struct UnkStruct_02278e34 {
    char pad_00[0xBC];
    struct Pair pair;
};

extern void *func_0202eb70(void *);
extern char data_ov076_02279744;
extern void *func_0202eb20(UnkStruct_02278e78 *);
extern void func_020edb3c(void *self);
extern void func_0201612c(void *p);
extern struct Pair __ptmf_null;

struct UnkStruct_02278e90 *func_ov076_02278e90(struct UnkStruct_02278e90 *this)
{
    func_0202eb70(this);
    this->unk_00 = &data_ov076_02279744;
    this->unk_B8 = 0xFFF1;
    return this;
}

UnkStruct_02278e78 *func_ov076_02278e78(UnkStruct_02278e78 *self)
{
    self->unk_00 = &data_ov076_02279744;
    func_0202eb20(self);
    return self;
}

void *func_ov076_02278e58(void *self)
{
    *(void **) self = &data_ov076_02279744;
    func_0202eb20((UnkStruct_02278e78 *) self);
    func_020edb3c(self);
    return self;
}

void func_ov076_02278e34(struct UnkStruct_02278e34 *p)
{
    func_0201612c(p);
    p->pair = __ptmf_null;
}
