/* func_ov004_022116fc @ 0x022116fc, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022116fc;
struct UnkStruct_022116fc_2;
extern void func_ov004_022118bc(struct UnkStruct_022116fc_2 *, int);

struct UnkStruct_022116fc {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_022116fc_2 {
    char pad_00[300];
    struct UnkStruct_022116fc *b;
};

void func_ov004_022116fc(struct UnkStruct_022116fc_2 *self)
{
    struct UnkStruct_022116fc *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_022118bc(self, 3);
        }
    }
}
