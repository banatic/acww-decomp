/* func_ov053_02261260 @ 0x02261260, 0x3c bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern unsigned short data_020c80f8;

struct UnkStruct_02261260 {
    unsigned char pad_00[0x71c];
    short unk_71C;
};

int func_ov053_02261260(struct UnkStruct_02261260 *obj)
{
    func_02019d0c((char *) obj + 0x564, 3, 1, 0, 0, 0, obj->unk_71C, 0, 0, data_020c80f8, 0);
    return 1;
}
