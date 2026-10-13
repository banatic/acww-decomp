/* func_020b6140 @ 0x020b6140, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char k;
    unsigned char pad_01;
    short unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char pad_16[6];
} UnkStruct_020b6140_4;

typedef struct {
    UnkStruct_020b6140_4 *unk_00;
    unsigned char unk_04;
} UnkStruct_020b6140;
typedef struct {
    unsigned char pad_00[0xc];
    UnkStruct_020b6140 *unk_0C;
} UnkStruct_020b6140_2;
typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_020b6140_3;

extern UnkStruct_020b6140_2 *data_021f6948;
extern UnkStruct_020b6140_3 *data_020ccf94;
extern int func_020b6214(void *p0, int idx, unsigned char *p2, int *p3, int *p4, short *p5, int *a, int *b, unsigned char *p6,
                         unsigned char *p7);
extern int func_02073dd4(UnkStruct_020b6140_3 *g, int v);

int func_020b6140(void *p0, int idx, unsigned char *p2, int *p3, int *p4, short *p5, unsigned char *p6, unsigned char *p7,
                  int *p8, int *p9)
{
    int a, b;
    int r;

    r = func_020b6214(p0, idx, p2, p3, p4, p5, &a, &b, p6, p7);
    if (p8 != 0) {
        *p8 = a;
    }
    if (p9 != 0) {
        *p9 = b;
    }
    if (r == 1) {
        if (idx != -1 && data_021f6948 != 0 && data_021f6948->unk_0C != 0 && data_021f6948->unk_0C->unk_00 != 0) {
            UnkStruct_020b6140_4 *arr = data_021f6948->unk_0C->unk_00;
            int n = data_021f6948->unk_0C->unk_04;
            if (idx >= 0 && idx < n) {
                UnkStruct_020b6140_4 *e = &arr[idx];
                unsigned char kind = e->k;
                if (e->unk_08 == 0) {
                    e->unk_08 = 0x200;
                }
                if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && kind == 7) {
                    kind = 8;
                }
                *p2 = kind;
                p3[0] = e->unk_04;
                p3[1] = e->unk_08;
                p3[2] = e->unk_0C;
                *p4 = e->unk_10;
                *p5 = e->unk_02;
                *p6 = e->unk_14;
                *p7 = e->unk_15;
                return r;
            }
        }
        return 0;
    }
    return r;
}
