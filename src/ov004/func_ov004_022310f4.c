/* func_ov004_022310f4 @ 0x022310f4, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022310f4;
struct UnkStruct_022310f4_2;
extern void func_ov004_0223121c(struct UnkStruct_022310f4_2 *, int);

struct UnkStruct_022310f4 {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_022310f4_2 {
    char pad_00[720];
    struct UnkStruct_022310f4 *b;
};

void func_ov004_022310f4(struct UnkStruct_022310f4_2 *self)
{
    struct UnkStruct_022310f4 *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_0223121c(self, 3);
        }
    }
}
