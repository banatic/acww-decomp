/* func_ov068_02274878 @ 0x02274878, 0x78 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern unsigned int data_020c814c;
extern int func_02019c20(void *p, int a, int b, int c, int d, int e);
extern void func_0201ad18(void *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_020147e0(void *p, int a, int b);

typedef struct StructWithOffsets {
    unsigned char pad_00[0x3b0];
    unsigned char unk_3B0;
    unsigned char pad_3B1[0x1b3];
    unsigned char unk_564;
    unsigned char pad_565[0xb3];
    unsigned char unk_618;
    unsigned char pad_619[0x117];
    unsigned int unk_730;
} StructWithOffsets;

extern unsigned char data_021fbee8[];

int func_ov068_02274878(StructWithOffsets *this)
{
    if (this->unk_730 == 7) {
        func_02019c20(&this->unk_564, 1, 0x102, 0, data_020c80f8, 0);
    }
    func_0201ad18(&this->unk_3B0, 4, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 0);
    func_020147e0(&this->unk_618, 0, 0);
    return 1;
}
