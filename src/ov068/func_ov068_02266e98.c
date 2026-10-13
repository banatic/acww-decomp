/* func_ov068_02266e98 @ 0x02266e98, 0x98 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_02091254(int, int *, int, int);
extern int func_0207dd84(int);
extern int func_020644cc(int);

typedef struct {
    signed char unk_00;
    unsigned short s16;
} UnkStruct_02266e98;

typedef struct {
    unsigned int data[525];
} UnkStruct_02266e98_2;

void func_ov068_02266e98(UnkStruct_02266e98 *a, UnkStruct_02266e98_2 *b)
{
    int local[3];

    if (a->unk_00 > 0) {
        a->unk_00--;
    }
    if (a->s16 != 0) {
        a->s16--;
    }

    if (a->unk_00 == 0) {
        local[0] = b->data[286]; // 0x478
        local[1] = b->data[287]; // 0x47c
        local[2] = b->data[288]; // 0x480

        func_02091254(0x81, local, 0, 0);

        if (func_0207dd84(b->data[524]) != 0) { // 0x830
            a->unk_00 = func_020644cc(15) + 15;
        } else {
            a->unk_00 = -1;
        }
    } else if (a->unk_00 == -1) {
        if (func_0207dd84(b->data[524]) != 0) { // 0x830
            a->unk_00 = func_020644cc(10) + 15;
        }
    }
}
