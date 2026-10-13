/* func_020ab58c @ 0x020ab58c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43ec;
extern void MI_CpuFill8(void *dest, int value, int size);
extern void func_020a8c1c(void *ptr);
extern void func_020a82b0(void *ptr);

struct UnkStruct_020ab58c {
    char pad_00[0x2d8];
    int unk_2D8;
    unsigned char unk_2DC;
    unsigned char unk_2DD[0x1a];
    char pad_2F7;
    unsigned char unk_2F8[0x5c];
    unsigned char unk_354[0xc];
    int unk_360;
};

void func_020ab58c(struct UnkStruct_020ab58c *obj)
{
    obj->unk_2D8 = -1;
    obj->unk_2DC = data_021f43ec;
    MI_CpuFill8(obj->unk_2DD, 0, 0x1a);
    func_020a8c1c(obj->unk_2F8);
    func_020a82b0(obj->unk_354);
    obj->unk_360 = 0;
}
