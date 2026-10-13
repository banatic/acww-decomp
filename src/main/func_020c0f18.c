/* func_020c0f18 @ 0x020c0f18, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void VEC_Add(void *, void *, void *);
extern unsigned char data_021fba88[0x11];

typedef struct {
    int pad_00;
    int unk_04;
    int pad_08[11];
    int unk_34;
    int unk_38;
    int pad_3C;
    int unk_40;
    int pad_44[7];
    int unk_60;
} UnkStruct_020c0f18;

void func_020c0f18(UnkStruct_020c0f18 *self)
{
    int x;
    int offscreen;
    int y;
    int visible;

    VEC_Add(&self->unk_34, &self->unk_40, &self->unk_34);
    x = self->unk_34 >> 12;
    y = self->unk_38 >> 12;
    if (y < -35 || y > 202 || x < -35 || x > 291) {
        offscreen = 1;
    } else {
        offscreen = 0;
    }
    if (self->unk_60 == 0 && offscreen == 0 && y > 0 && y < 192 && x > 0 && x < 256) {
        visible = 1;
    } else {
        visible = 0;
    }
    data_021fba88[0x10] = visible;
    if (offscreen != 0) {
        self->unk_04 = 3;
    }
}
