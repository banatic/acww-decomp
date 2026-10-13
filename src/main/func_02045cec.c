/* func_02045cec @ 0x02045cec, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[2];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 6;
    unsigned char pad_03[5];
    unsigned short unk_08;
    unsigned char pad_0A[6];
} UnkStruct_02045cec;

typedef struct {
    int unk_00;
    int unk_04;
} Key;

extern UnkStruct_02045cec data_021c7884[];

int func_02045cec(Key *k, int flag)
{
    UnkStruct_02045cec *e;
    int i;
    int res;
    volatile unsigned short a;
    volatile unsigned short b;
    volatile unsigned short w;
    unsigned short v;

    res = -1;
    e = data_021c7884;
    for (i = 0; i < 0x14; e++, i++) {
        w = e->unk_08;
        v = w;
        a = v;
        if (k->unk_00 != (a >> 8)) {
            continue;
        }
        b = v;
        if (k->unk_04 != (b & 0xff)) {
            continue;
        }
        if (flag != e->b1) {
            continue;
        }
        res = i;
        break;
    }
    return res;
}
