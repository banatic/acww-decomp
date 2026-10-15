/* func_ov068_0226e688 @ 0x0226e688, 0x80 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern unsigned short data_020c80f8;

typedef struct {
    unsigned char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    unsigned char pad_68[0x564 - 0x68];
    char unk_564[0x1b4];
    int unk_718;
    int unk_71C;
    int unk_720;
    unsigned char unk_724;
} UnkStruct_0226e688;

int func_ov068_0226e688(UnkStruct_0226e688 *r4)
{
    r4->unk_718 = r4->unk_5C;
    r4->unk_71C = r4->unk_60;
    r4->unk_720 = r4->unk_64;
    r4->unk_718 -= 0x2000;
    r4->unk_720 += 0xa000;
    func_02019d0c(r4->unk_564, 2, 1, r4->unk_718, r4->unk_720, 0, 0, 0, 0, data_020c80f8, 0);
    r4->unk_724 = 0x3c;
    return 1;
}
