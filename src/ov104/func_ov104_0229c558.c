/* func_ov104_0229c558 @ 0x0229c558, 0xf0 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O1,s
 */

extern int func_02073d90(void *);
extern int func_02097890(void *, int);
extern void func_ov104_0229c354(void *, int);
extern void func_ov104_0229c344(void *, int);
extern void func_ov104_0229c3dc(void *);
extern int func_ov104_0229c870(void *, void *, int);
extern int func_ov104_0229c9c4(void *, void *);

typedef struct {
    unsigned char pad_00[0xb0];
    unsigned short flags;  // 0xb0
    unsigned short unk_B2; // 0xb2
    unsigned char pad_B4[0xbe - 0xb4];
    unsigned char unk_BE; // 0xbe
} UnkStruct_0229c558;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} GStruct;

extern GStruct *data_020ccf94;

void func_ov104_0229c558(UnkStruct_0229c558 *self)
{
    GStruct *g = data_020ccf94;

    if (func_02073d90(g) == 0) {
        return;
    }

    func_ov104_0229c354(self, 0x800);
    self->unk_B2 = 0;

    {
        int r = func_02097890((char *) self + 0x2db4, 10);
        self->flags = 0;

        if (r > 0) {
            goto positive;
        }

        // r <= 0
        self->flags = 4;
        func_ov104_0229c344(self, 0x1000);
        return;

    positive:
        if (func_ov104_0229c9c4(self, (char *) self + 0x2db4) != 0) {
            self->flags |= 0x800;
        }

        if (g->unk_64 == 0) {
            goto zero;
        }

        // g->unk_64 != 0
        func_ov104_0229c354(self, 0x1000);
        self->unk_BE = 0;
        func_ov104_0229c344(self, 0x2000);
        func_ov104_0229c3dc(self);
        return;

    zero:
        func_ov104_0229c354(self, 0x4000);
        self->flags |= func_ov104_0229c870(self, (char *) self + 0x2db4, 1);
        if (self->flags & 0x10) {
            self->flags |= 0x400;
        }
    }
}
