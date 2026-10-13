/* func_020bb4e0 @ 0x020bb4e0, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020bb4e0 {
    unsigned char pad_00[0x1208];
    int unk_1208;
    int unk_120C;
    unsigned char pad_1210[0x1528 - 0x1210];
    int unk_1528;
    unsigned char pad_152C[0x1570 - 0x152c];
    int unk_1570;
    int unk_1574;
    int unk_1578;
    unsigned char pad_157C[0x1584 - 0x157c];
    unsigned char *unk_1584;
    unsigned char pad_1588[0x158c - 0x1588];
    int unk_158C;
} UnkStruct_020bb4e0;

extern int func_02002b40(unsigned char *p, int a, int b, int c);
extern void func_020bb7e0(UnkStruct_020bb4e0 *self, int a, int b);

void func_020bb4e0(UnkStruct_020bb4e0 *self)
{
    int idx;
    int t;
    int n;
    int off;

    idx = self->unk_1578;
    t = ((self->unk_1208 >> 8) - 8) & 0xff;
    if ((t >> 3) == idx) {
        off = (t >> 3) * 0x20;
        if (func_02002b40(self->unk_1584 + off, 6, 0x20, off) != 0) {
            n = self->unk_120C;
            idx = idx + 1;
            n = n + 1;
            if (idx >= 0x20) {
                idx = -1;
                n = 0x20;
                func_020bb7e0(self, self->unk_1528, self->unk_1528);
                self->unk_1570 = self->unk_1574;
                self->unk_158C = 3;
            }
            self->unk_1578 = idx;
            self->unk_120C = n;
        }
    }
}
