/* func_020c1334 @ 0x020c1334, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec;
typedef struct {
    char pad_00[0x4];
    int unk_04;
    char pad_08[0x34 - 0x08];
    Vec unk_34;
    Vec unk_40;
    char pad_4C[0x60 - 0x4c];
    int unk_60;
    int unk_64;
    int unk_68;
} UnkStruct_020c1334;
extern int data_020d22e4[];
extern void *func_020961a8(int);
extern void VEC_Add(void *, void *, void *);
void func_020c1334(UnkStruct_020c1334 *self)
{
    int *p = &self->unk_34.x;
    VEC_Add(&self->unk_34, &self->unk_40, &self->unk_34);
    {
        void *r = func_020961a8(4);
        if (r != 0) {
            int delta = (-(*(int *) ((char *) r + 0x5c) - *(int *) ((char *) r + 0x68))) * data_020d22e4[self->unk_68] >> 12;
            *p += delta;
        }
    }
    if (p[1] > ((self->unk_60 << 12) + 0x100000)) {
        self->unk_04 = 3;
    } else if (*p < -0x14000) {
        *p += 0x11e000;
    } else if (*p > 0x114000) {
        *p -= 0x11e000;
    }
}
