/* func_ov004_02216248 @ 0x02216248, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02216248;
struct UnkStruct_02216248_2;
extern void func_ov004_022164a0(struct UnkStruct_02216248_2 *, int);

struct UnkStruct_02216248 {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_02216248_2 {
    char pad_00[300];
    struct UnkStruct_02216248 *b;
};

void func_ov004_02216248(struct UnkStruct_02216248_2 *self)
{
    struct UnkStruct_02216248 *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_022164a0(self, 5);
        }
    }
}
