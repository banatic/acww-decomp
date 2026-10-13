/* func_ov003_0221bd6c @ 0x0221bd6c, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221bd6c;
struct UnkStruct_0221bd6c_2;
extern void func_ov003_0221bfa8(struct UnkStruct_0221bd6c_2 *, int);

struct UnkStruct_0221bd6c {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_0221bd6c_2 {
    char pad_00[300];
    struct UnkStruct_0221bd6c *b;
};

void func_ov003_0221bd6c(struct UnkStruct_0221bd6c_2 *self)
{
    struct UnkStruct_0221bd6c *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov003_0221bfa8(self, 3);
        }
    }
}
