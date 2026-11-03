/* atm: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220c054 @ 0x0220c054, 0x24 bytes, Thumb
 * func_ov004_0220c050 @ 0x0220c050, 0x4 bytes, Thumb
 * func_ov004_0220c020 @ 0x0220c020, 0x30 bytes, Thumb
 * func_ov004_0220c01c @ 0x0220c01c, 0x2 bytes, Thumb
 */

struct UnkStruct_0220c054 {
    int unk_00;
    void *unk_04;
};

struct UnkStruct_0220c054_2 {
    char pad_00[0x12c];
    struct UnkStruct_0220c054 *unk_12C;
};

struct Node {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0220c020 {
    char pad_00[0x12c];
    struct Node *unk_12C;
};

extern int func_ov004_0220c144(struct UnkStruct_0220c054_2 *obj, int arg);
extern void func_0203ee08(void *a, void *b);
extern int func_0203e020(void *a);

void func_ov004_0220c054(struct UnkStruct_0220c054_2 *obj)
{
    if (obj->unk_12C != 0) {
        if (obj->unk_12C->unk_04 != 0) {
            func_ov004_0220c144(obj, 2);
        }
    }
}

int func_ov004_0220c050(void *callbackObject)
{
    return 1;
}

void func_ov004_0220c020(struct UnkStruct_0220c020 *self)
{
    if (self->unk_12C != 0 && self->unk_12C->unk_04 == 0) {
        void *p = self;
        if (self != 0) {
            p = (char *) self + 0xec;
        }
        func_0203ee08(self, p);
        func_0203e020(self);
    }
}

void func_ov004_0220c01c(void *object) {}
