/* func_02045c84 @ 0x02045c84, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// Twin of func_02045cec with an extra check on the low three bits of byte 0.

typedef struct {
    unsigned char a : 3;
    unsigned char : 5;
    unsigned char pad_01;
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 6;
    unsigned char pad_03[5];
    unsigned short unk_08;
    unsigned char pad_0A[6];
} UnkStruct_02045c84;

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

extern UnkStruct_02045c84 data_021c7884[];

int func_02045c84(unsigned int p0, Pair *p1, unsigned int p2)
{
    UnkStruct_02045c84 *e;
    int i;
    int res;
    volatile unsigned short a;
    volatile unsigned short b;
    volatile unsigned short w;
    unsigned short v;

    i = 0;
    res = -1;
    e = data_021c7884;
    for (; i < 0x14; e++, i++) {
        if (p0 != e->a) {
            continue;
        }
        w = e->unk_08;
        v = w;
        a = v;
        if (p1->unk_00 != (a >> 8)) {
            continue;
        }
        b = v;
        if (p1->unk_04 != (b & 0xff)) {
            continue;
        }
        if (p2 != e->b1) {
            continue;
        }
        res = i;
        break;
    }
    return res;
}
