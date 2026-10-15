/* func_ov004_0222f5cc @ 0x0222f5cc, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222f5cc;
struct UnkStruct_0222f5cc_2;
extern int func_ov004_0222f6e8(struct UnkStruct_0222f5cc_2 *, int);

struct UnkStruct_0222f5cc {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_0222f5cc_2 {
    char pad_00[720];
    struct UnkStruct_0222f5cc *b;
};

void func_ov004_0222f5cc(struct UnkStruct_0222f5cc_2 *self)
{
    struct UnkStruct_0222f5cc *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_0222f6e8(self, 2);
        }
    }
}
