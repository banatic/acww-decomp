/* func_ov147_02299018 @ 0x02299018, 0xc4 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char b[0x20];
} UnkStruct_02299018;

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    char pad_A8[0x28];
    char unk_D0;
} Object;

extern void func_ov147_02298f20(Object *self, UnkStruct_02299018 *e, int y, int x);
extern int func_020b9c10(void *dst, void *src, int a, int b, int c, int d);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);

extern UnkStruct_02299018 data_ov147_0229b0cc[];
extern char data_ov147_0229baac[];
extern char data_ov147_0229f2ac[];

int func_ov147_02299018(Object *self)
{
    int i;
    int x;
    int y;
    UnkStruct_02299018 *e;
    int yy;
    y = self->unk_A4;
    if (y < 0x36) {
        y += 9;
        for (i = 0; i < 15 && y >= 9; i++, y--) {
            e = &data_ov147_0229b0cc[i];
            yy = y;
            x = 0;
            if (yy > 0x1f) {
                x = yy - 0x1f;
                yy = 0x1f;
            }
            for (; yy >= 0 && x < 0x18; yy--, x++) {
                if (x < 0x15) {
                    func_ov147_02298f20(self, e, yy, x);
                }
            }
        }
        func_020b9c10(&self->unk_D0, data_ov147_0229f2ac, 5, 0x140, 0x140, 0x2ff);
        self->unk_A4 = self->unk_A4 + 1;
    } else {
        MI_CpuCopy8(data_ov147_0229baac, data_ov147_0229f2ac, 0x3800);
        func_020b9c10(&self->unk_D0, data_ov147_0229f2ac, 5, 0x140, 0x140, 0x2ff);
        return 1;
    }
    return 0;
}
