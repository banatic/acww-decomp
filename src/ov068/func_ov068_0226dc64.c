/* func_ov068_0226dc64 @ 0x0226dc64, 0x5c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int val);

struct TableEntry {
    unsigned short x;
    unsigned short y;
    unsigned char pad_04[8];
};

extern struct TableEntry data_020ca17c[];

struct UnkStruct_0226dc64 {
    unsigned char pad_00[0x21c];
    unsigned short unk_21C;
    unsigned char pad_21E[2];
    unsigned short unk_220;
    unsigned char pad_222[2];
    unsigned char unk_224;
};

void func_ov068_0226dc64(struct UnkStruct_0226dc64 *self, unsigned char v)
{
    self->unk_224 = v;
    if (self->unk_224 >= 4) {
        self->unk_224 = 0;
    }

    self->unk_220 = data_020ca17c[self->unk_224].x;
    self->unk_220 += func_020644cc(data_020ca17c[self->unk_224].y);
    self->unk_21C = 0;
}
