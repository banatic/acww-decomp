/* func_02018e30 @ 0x02018e30, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int unk_00;
    unsigned char pad_04[8];
    int unk_0C;
} UnkStruct_02018e30;

typedef struct {
    unsigned char pad_00[0xa4];
    UnkStruct_02018e30 *a4;
    unsigned char a8;
    unsigned char a9;
} UnkStruct_02018e30_2;

typedef struct {
    unsigned char pad_00[0x190];
    unsigned int unk_190;
    unsigned char pad_194[0x334 - 0x194];
    unsigned char unk_334[0x420 - 0x334];
    unsigned char unk_420[0x445 - 0x420];
    unsigned char unk_445;
    unsigned char pad_446[0x628 - 0x446];
    int unk_628;
} UnkStruct_02018e30_3;

extern int func_020164cc(void *p, void *q);
extern void func_02016764(void *a, UnkStruct_02018e30_3 *b, int c, int d, int e, int f, int g, int h);
extern void func_02012444(int a, unsigned short b, int c);
extern void func_0201a698(void *a, UnkStruct_02018e30 *b, int c);
extern void func_02019af0(UnkStruct_02018e30_2 *s, int v);
extern unsigned short data_020c80f8;

void func_02018e30(UnkStruct_02018e30_2 *s, UnkStruct_02018e30_3 *o)
{
    UnkStruct_02018e30 *q = s->a4;
    if (q != 0) {
        if (s->a8 == 1) {
            if (func_020164cc(o->unk_334, o) != 0) {
                UnkStruct_02018e30 *q2 = s->a4;
                int *pv = &q2->unk_0C;
                int v = *pv;
                if (v < 0x137) {
                    unsigned short w = data_020c80f8;
                    int t;
                    func_02016764(o->unk_334, o, *pv, data_020c80f8, 0, 0x1000, 0, 0);
                    t = o->unk_628;
                    if (t != 0) {
                        func_02012444(t, w, 0);
                    }
                    o->unk_445 = s->a9;
                    func_0201a698(o->unk_420, s->a4, 1);
                    s->a8 = 0;
                } else if (v == 0x137) {
                    func_02019af0(s, 1);
                }
            }
        } else {
            if (q->unk_00 == 0) {
                unsigned int x = (o->unk_190 << 4) >> 16;
                if (x == 0) {
                    func_02019af0(s, 1);
                }
            }
        }
    }
}
