/* func_ov004_02216cf8 @ 0x02216cf8, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02216cf8;
struct UnkStruct_02216cf8_2;
extern void func_ov004_02217124(struct UnkStruct_02216cf8_2 *, int);

struct UnkStruct_02216cf8 {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_02216cf8_2 {
    char pad_00[300];
    struct UnkStruct_02216cf8 *b;
};

void func_ov004_02216cf8(struct UnkStruct_02216cf8_2 *self)
{
    struct UnkStruct_02216cf8 *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_02217124(self, 10);
        }
    }
}
