/* func_0206d56c @ 0x0206d56c, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051648(void *p);

struct UnkStruct_0206d56c;
struct UnkStruct_0206d56c_2;

struct UnkStruct_0206d56c {
    unsigned char pad_00[0x30];
    struct UnkStruct_0206d56c_2 *b;
};

struct UnkStruct_0206d56c_2 {
    unsigned char pad_00[0x10];
    int unk_10;
    unsigned char pad_14[0x1C];
    int unk_30;
};

int func_0206d56c(struct UnkStruct_0206d56c *a, int value, int flag)
{
    int result = 0;
    if (flag && a->b != 0) {
        a->b->unk_10 = value;
        func_02051648(a->b);
        result = a->b->unk_30;
        a->b->unk_10 = 0;
    }
    return result;
}
