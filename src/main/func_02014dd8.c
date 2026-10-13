/* func_02014dd8 @ 0x02014dd8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern void func_02068440(int a);

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x8];
    int unk_4C;
    char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_02014dd8;

int func_02014dd8(UnkStruct_02014dd8 *self)
{
    if (self->unk_4C != 0 && self->unk_40 != 0) {
        if (func_02019d0c(self->unk_4C + 0x564, 0x12, 4, 0, 0, 0, 0, 0, 0, data_020c80f8, 0) != 0) {
            func_02068440(self->unk_40);
            self->unk_AC = 1;
        }
    }
    return 0;
}
