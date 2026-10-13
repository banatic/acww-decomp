/* func_ov003_0220ef1c @ 0x0220ef1c, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75b8;

struct UnkStruct_0220ef1c {
    unsigned char pad_00[0x2d8];
    unsigned int : 12;
    unsigned int bits : 16;
    unsigned int : 4;
    unsigned char pad_2DC[0x428];
    int unk_704;
};

extern void func_02010f5c(struct UnkStruct_0220ef1c *p);
extern void func_0200f888(struct UnkStruct_0220ef1c *p);
extern void func_0200f95c(struct UnkStruct_0220ef1c *p);

void func_ov003_0220ef1c(struct UnkStruct_0220ef1c *p)
{
    unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag > 0) {
        func_02010f5c(p);
        if (p->unk_704 == 0x6a) {
            if (p->bits == 0x13 || p->bits == 0x19 || p->bits == 0x1e) {
                func_0200f888(p);
            }
        } else {
            func_0200f95c(p);
        }
    }
}
