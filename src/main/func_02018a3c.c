/* func_02018a3c @ 0x02018a3c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02018a3c {
    unsigned char pad_00[0x98];
    unsigned char unk_98;
};

struct UnkStruct_02018a3c_2 {
    unsigned char pad_00[0x18c];
    unsigned int unk_18C;
    unsigned int unk_190;
};

extern int func_02019de8(struct UnkStruct_02018a3c *p0);
extern void func_02019af0(struct UnkStruct_02018a3c *p0, int value);

void func_02018a3c(struct UnkStruct_02018a3c *p0, struct UnkStruct_02018a3c_2 *p1)
{
    unsigned int a;
    unsigned int b;

    if (p0->unk_98 < 1) {
        return;
    }
    if (func_02019de8(p0) != 0) {
        return;
    }
    a = (p1->unk_190 << 4) >> 16;
    b = (p1->unk_18C << 4) >> 16;
    if ((int) a < (int) (b - 0x1000)) {
        return;
    }
    func_02019af0(p0, 1);
}
