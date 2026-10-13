/* func_0203fbb0 @ 0x0203fbb0, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned int unk_04;
    unsigned int unk_08;
} Rec;
typedef union {
    unsigned int word;
    unsigned char b[4];
} Packed;
typedef struct {
    Packed p;
    Rec r;
} Comb;
typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char pad_04[0x18];
} UnkStruct_0203fbb0;

extern unsigned char func_0209de88(int t, int a, int b, int c);
extern void func_02040164(Rec *out, int max);
extern int func_0203ff98(Rec *r, UnkStruct_0203fbb0 *e, int t, Packed p);
extern int func_02040034(UnkStruct_0203fbb0 *e, Packed p, Rec *r, Rec *out, int count, int one, int zero);
extern void func_02040010(Rec *r, Packed p);
extern UnkStruct_0203fbb0 data_020dac08[];

int func_0203fbb0(Rec *out, int max, const unsigned char *src)
{
    Comb c;
    UnkStruct_0203fbb0 *e;
    int i;
    int count = 0;
    int t = src[5];

    {
        int a = src[4], b;
        c.p.b[3] = a;
        b = src[3];
        c.p.b[2] = b;
        c.p.b[1] = 12;
        c.p.b[0] = func_0209de88(t, a, b, 12);
    }
    func_02040164(out, max);
    e = data_020dac08;
    for (i = 0; i < 0x63; e++, i++) {
        if (e->unk_02 == 5) {
            continue;
        }
        if (func_0203ff98(&c.r, e, t, c.p) == 0) {
            continue;
        }
        if (c.r.unk_04 >= c.p.word) {
            continue;
        }
        if (c.r.unk_08 <= c.p.word) {
            continue;
        }
        if (func_02040034(e, c.p, &c.r, out, count, 1, 0) != 0) {
            continue;
        }
        func_02040010(&c.r, c.p);
        {
            Rec *d = &out[count];
            d->unk_00 = c.r.unk_00;
            d->unk_02 = c.r.unk_02;
            d->unk_04 = c.r.unk_04;
            d->unk_08 = c.r.unk_08;
        }
        count++;
        if (count == max) {
            break;
        }
    }
    return count;
}
