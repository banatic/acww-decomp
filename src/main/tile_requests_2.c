/* tile_requests_2: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02042fd4 @ 0x02042fd4, 0x24 bytes, Thumb
 * func_02042fc4 @ 0x02042fc4, 0x10 bytes, Thumb
 * func_02042f20 @ 0x02042f20, 0xa4 bytes, Thumb
 * func_02042f10 @ 0x02042f10, 0xe bytes, Thumb
 * func_02042f08 @ 0x02042f08, 0x8 bytes, Thumb
 * func_02042efc @ 0x02042efc, 0xa bytes, Thumb
 * func_02042e64 @ 0x02042e64, 0x98 bytes, Thumb
 * func_02042e10 @ 0x02042e10, 0x54 bytes, Thumb
 */

typedef struct {
    int a, b;
} Pair;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned short unk_10;
    unsigned short unk_12;
    int unk_14;
    int unk_18;
    unsigned char unk_1C;
    unsigned char unk_1D;
    signed char unk_1E;
    unsigned char pad_1F;
    int unk_20;
} Slot;

struct UnkStruct_02042e64 {
    unsigned short unk_00;
    unsigned short pad_02;
    signed short unk_04;
};

typedef struct {
    char unk_00;
    char unk_01;
    short unk_02;
    short unk_04;
} UnkStruct_02042e10;

typedef struct {
    int unk_00;
    int w1;
} UnkStruct_02042e10_2;

extern void func_0204811c(void *dst, const void *src);
extern unsigned char data_021c779c[];
extern unsigned char data_021c7c48[];
extern int func_0209a1d0(void);
extern int func_02099fe8(void);
extern unsigned char func_020b65c4(void);
extern int func_020a6ff0(int);
extern void func_02045770(unsigned char i, int p1);
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern int func_02045cec(int *, int);
extern int func_0204e414(void);
extern unsigned short *func_0204f5e0(int, int, int, int, int, int);
extern void func_0204a330(int, int, int, int);
extern int func_0205be38(void);
extern void func_02042d94(UnkStruct_02042e10 *a, UnkStruct_02042e10_2 *b);

void func_02042efc(short *p);

void func_02042fd4(void *src)
{
    struct {
        unsigned int a;
        unsigned int b;
        unsigned int c;
    } local;
    unsigned int *p = (unsigned int *) src;
    local.a = p[0];
    local.b = p[1];
    local.c = p[2];
    func_0204811c((void *) data_021c779c, &local);
}

void *func_02042fc4(int index)
{
    return &data_021c7c48[index * 0x24];
}

int func_02042f20(Slot *slot, int a1, int a2, Pair *a3, unsigned short p5, unsigned short p6, unsigned char p7,
                  unsigned char p8, int p9, signed char p10)
{
    int i;
    int r;
    int va, vb;

    r = -1;
    for (i = 0; i < 3; slot++, i++) {
        if (slot->unk_08 != 0 || slot->unk_0C != 0) {
            continue;
        }
        if (a2 == 3 || a2 == 9 || a2 == 0x15) {
            if (p6 == 0x1520) {
                if (func_0209a1d0() == 0) {
                    a2++;
                }
            } else {
                if (func_02099fe8() < 0) {
                    a2++;
                }
            }
        }
        slot->unk_00 = a1;
        slot->unk_04 = func_020a6ff0((int) func_020b65c4());
        slot->unk_08 = 1;
        slot->unk_0C = a2;
        slot->unk_10 = p5;
        slot->unk_12 = p6;
        va = a3->a;
        vb = a3->b;
        slot->unk_14 = va;
        slot->unk_18 = vb;
        slot->unk_1C = p8;
        slot->unk_1D = p7;
        slot->unk_20 = p9;
        slot->unk_1E = p10;
        func_02045770((unsigned char) i, p9);
        r = i;
        break;
    }
    return r;
}

// placeholder, not used directly
void func_02042f10(void *r0, int r1)
{
    int *p;
    p = (int *) ((char *) r0 + 0x24 * r1);
    p[2] = 0;
    p[3] = 0;
}

void func_02042f08(short *argument0)
{
    func_02042efc((short *) argument0);
}

void func_02042efc(short *p)
{
    p[1] = 0;
    p[2] = -1;
}

void func_02042e64(struct UnkStruct_02042e64 *p)
{
    int hi, lo;
    int arr[2];
    int ret, ret2;
    int v;
    unsigned short *p2;
    int h, l, llo, hlo;

    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    if (p->unk_04 > 0) {
        p->unk_04--;
    }
    if (p->unk_04 != 0) {
        return;
    }

    hi = p->unk_00 >> 8;
    lo = p->unk_00 & 0xff;
    arr[0] = hi;
    arr[1] = lo;

    ret = func_02045cec(arr, 0);
    if (ret >= 0) {
        return;
    }

    v = 0xe3;
    ret2 = func_0204e414();
    p->unk_04 = -1;
    if (ret2 != 0) {
        h = hi >> 4;
        l = lo >> 4;
        llo = lo - (l << 4);
        hlo = hi - (h << 4);
        p2 = func_0204f5e0(ret2, h, l, hlo, llo, 0);
        if (p2 != 0) {
            int val = *p2;
            int rem = (val - 0xe8) % 5;
            v = (unsigned short) (rem + 0xe3);
        }
    }

    func_0204a330(p->unk_00 >> 8, p->unk_00 & 0xff, v, 0);
}

void func_02042e10(UnkStruct_02042e10 *a, UnkStruct_02042e10_2 *b)
{
    UnkStruct_02042e10_2 buf;

    if (a->unk_04 < 0) {
        int y = b->w1;
        int x = b->unk_00;

        a->unk_01 = x;
        a->unk_00 = y;
        a->unk_04 = ((func_0205be38() * 960) >> 12) + 150;
    }
    a->unk_02++;
    if (a->unk_02 >= 8) {
        a->unk_02 = 8;
    }
    buf.unk_00 = b->unk_00;
    buf.w1 = b->w1;
    func_02042d94(a, &buf);
}
