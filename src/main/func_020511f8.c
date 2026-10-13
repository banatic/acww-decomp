/* func_020511f8 @ 0x020511f8, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020511f8 {
    char pad_00[0x1c];
    int unk_1C;
    char pad_20[0xc];
    int unk_2C;
    char pad_30[9];
    unsigned char unk_39;
    char pad_3A[0x16];
    int unk_50;
    char pad_54[2];
    unsigned char unk_56;
    char pad_57[9];
    unsigned int unk_60;
    char pad_64[0xc];
    int unk_70;
} UnkStruct_020511f8;

typedef void (*Fn)(unsigned char *buf, int a, unsigned int n);

extern unsigned char data_021c8344[];
extern Fn data_020cb920[];
extern Fn data_020cb938[];

extern void DC_FlushRange(unsigned char *buf, unsigned int n);
extern void MI_CpuCopy8(unsigned char *dst, int src, unsigned int n);

void func_020511f8(UnkStruct_020511f8 *self)
{
    unsigned int n;
    unsigned char *p;
    unsigned char *q;
    unsigned char *end;
    unsigned int hi;
    unsigned int k;

    n = self->unk_60;
    if (n > 0x400) {
        n = 0x400;
    }
    DC_FlushRange(data_021c8344, n);
    if (self->unk_50 == 2 || self->unk_50 == 3) {
        data_020cb920[self->unk_2C](data_021c8344, self->unk_70, n);
    }
    if (self->unk_50 == 1 || self->unk_50 == 3) {
        data_020cb938[self->unk_2C](data_021c8344, self->unk_70, n);
    }
    if (self->unk_50 != 0) {
        return;
    }
    if (self->unk_56 != 0) {
        p = (unsigned char *) (self->unk_1C + self->unk_70);
        q = data_021c8344;
        end = data_021c8344 + n;
        k = self->unk_39;
        hi = (unsigned char) (k << 4);
        while (q < end) {
            if ((*p & 0xf0) == hi) {
                *p &= 0x0f;
                *p |= *q & 0xf0;
            }
            if ((*p & 0x0f) == k) {
                *p &= 0xf0;
                *p |= *q & 0x0f;
            }
            q++;
            p++;
        }
    } else {
        MI_CpuCopy8(data_021c8344, self->unk_1C + self->unk_70, n);
    }
}
