/* func_ov009_0226321c @ 0x0226321c, 0xac bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ed8(int, int);
extern int FX_MulFunc(int, int);
extern void func_01ffd070(int *, int, int *);
extern int func_02032754(void *);

typedef struct UnkStruct_0226321c {
    unsigned char pad_00[0x28];
    int unk_28;
    unsigned char pad1[4];
    int unk_30;
} UnkStruct_0226321c;

typedef struct UnkStruct_0226321c_2 {
    unsigned char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    unsigned char pad1[0x28c - 0x68];
    UnkStruct_0226321c *unk_28C;
    unsigned char flag290;
} UnkStruct_0226321c_2;

int func_ov009_0226321c(UnkStruct_0226321c_2 *self, int *out, short *b)
{
    if (self->unk_28C && self->flag290) {
        int v;
        int arr[4];
        int dest[3];

        v = func_020e8ed8(self->unk_28C->unk_28, self->unk_28C->unk_30);
        arr[0] = FX_MulFunc(0x1000, self->unk_28C->unk_30);
        arr[1] = FX_MulFunc(0x1000, self->unk_28C->unk_28);
        arr[2] = 0;
        arr[3] = arr[0];

        if (b) {
            *b = (short) (v + 0x8000);
        }

        if (out) {
            func_01ffd070(dest, func_02032754(self->unk_28C), &arr[1]);
            out[0] = dest[0];
            out[1] = dest[1];
            out[2] = dest[2];
            out[1] = 0x200;
            out[2] -= 0x200;
        }

        return 1;
    } else {
        out[0] = self->unk_5C;
        out[1] = self->unk_60;
        out[2] = self->unk_64;
        return 0;
    }
}
