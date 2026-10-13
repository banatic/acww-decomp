/* func_0201b1a4 @ 0x0201b1a4, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    int unk_00;
    short unk_04;
    unsigned char pad1[2];
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
    unsigned char pad2[3];
} Rec;

typedef struct {
    int x, y, z;
    unsigned char pad1[0x30 - 0xc];
    int idx30;
    unsigned char pad2[0x36 - 0x34];
    short unk_36;
    unsigned char pad_38[0x50 - 0x38];
    int unk_50;
    unsigned char unk_54;
} SelfT;

extern Rec data_020c822c[];
extern int func_02016884(void *a, int b, void *c);
extern void func_020164ec(void *a, void *arg1, int b, unsigned short c, int d);
extern void func_02016764(void *a, void *arg1, int b, unsigned short c, int d, int e, int f, int g);

void func_0201b1a4(SelfT *self, void *arg1, int idx, int flag4, unsigned short p5)
{
    Rec *rec;
    VecFx32 *arr;
    VecFx32 *q;

    if (idx < 0 || idx >= 5) {
        idx = 0;
    }

    rec = &data_020c822c[idx];

    arr = (VecFx32 *) ((char *) self + 0xc);
    q = &arr[rec->unk_08];
    self->x = arr[rec->unk_08].x;
    self->y = q->y;
    self->z = q->z;

    if (flag4 == 0) {
        self->unk_36 = rec->unk_04;
    } else {
        self->unk_36 = (short) flag4;
    }

    self->unk_50 = rec->unk_0C;

    if (idx != 4) {
        if ((self->unk_54 == 1 && rec->unk_10 == 1) ||
            func_02016884((char *) arg1 + 0x334, rec->unk_00, (char *) arg1 + 0x2a0)) {
            func_020164ec((char *) arg1 + 0x334, arg1, rec->unk_00, p5, 0);
        } else {
            func_02016764((char *) arg1 + 0x334, arg1, rec->unk_00, p5, 0, 0x1000, 0, 0);
        }
    }

    self->idx30 = idx;
    self->unk_54 = rec->unk_10;
}
