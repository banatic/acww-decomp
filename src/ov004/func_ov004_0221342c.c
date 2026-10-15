/* func_ov004_0221342c @ 0x0221342c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221342c;
struct UnkStruct_0221342c_2;
extern int func_ov004_02213590(struct UnkStruct_0221342c_2 *, int);

struct UnkStruct_0221342c {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_0221342c_2 {
    char pad_00[300];
    struct UnkStruct_0221342c *b;
};

void func_ov004_0221342c(struct UnkStruct_0221342c_2 *self)
{
    struct UnkStruct_0221342c *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_02213590(self, 3);
        }
    }
}
