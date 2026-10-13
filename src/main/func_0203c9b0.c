/* func_0203c9b0 @ 0x0203c9b0, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short unk_00;
    short unk_02;
    int v0;
    int v1;
    int v2;
    int v3;
} Entry;

typedef struct {
    char pad_00[0xfc];
    short sLow;
    short sHigh;
    int unk_100;
    int unk_104;
    int unk_108;
    int unk_10C;
} Dest;

extern Entry data_020ca20c[];
extern void func_020eac34(int *, int *, int);
extern void VEC_Add(int *, int *, int *);
extern int FX_MulFunc(int, int);

void func_0203c9b0(Dest *dst, int a, int b, int t)
{
    int val4;
    int diff[3];
    int buf[3];
    short a2;
    short a0;

    diff[0] = data_020ca20c[b].v1 - data_020ca20c[a].v1;
    diff[1] = data_020ca20c[b].v2 - data_020ca20c[a].v2;
    diff[2] = data_020ca20c[b].v3 - data_020ca20c[a].v3;

    dst->unk_104 = data_020ca20c[a].v1;
    dst->unk_108 = data_020ca20c[a].v2;
    dst->unk_10C = data_020ca20c[a].v3;

    val4 = data_020ca20c[a].v0;
    dst->unk_100 = val4;

    a2 = data_020ca20c[a].unk_02;
    dst->sHigh = a2;
    a0 = data_020ca20c[a].unk_00;
    dst->sLow = a0;

    func_020eac34(buf, diff, t);
    VEC_Add(&dst->unk_104, buf, &dst->unk_104);

    dst->unk_100 += FX_MulFunc(data_020ca20c[b].v0 - val4, t);
    dst->sHigh += (short) FX_MulFunc((short) (data_020ca20c[b].unk_02 - a2), t);
    dst->sLow += (short) FX_MulFunc((short) (data_020ca20c[b].unk_00 - a0), t);
}
