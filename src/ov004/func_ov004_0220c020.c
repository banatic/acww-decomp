/* func_ov004_0220c020 @ 0x0220c020, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ee08(void *a, void *b);
extern int func_0203e020(void *a);

struct Node {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0220c020 {
    char pad_00[0x12c];
    struct Node *unk_12C;
};

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
