/* outdoor_villager_3: 8 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02266f40 @ 0x02266f40, 0x2 bytes, Thumb
 * func_ov068_02266f3c @ 0x02266f3c, 0x2 bytes, Thumb
 * func_ov068_02266f30 @ 0x02266f30, 0xa bytes, Thumb
 * func_ov068_02266e98 @ 0x02266e98, 0x98 bytes, Thumb
 * func_ov068_02266e80 @ 0x02266e80, 0x18 bytes, Thumb
 * func_ov068_02266e7c @ 0x02266e7c, 0x4 bytes, Thumb
 * func_ov068_02266e78 @ 0x02266e78, 0x4 bytes, Thumb
 * func_ov068_02266df4 @ 0x02266df4, 0x84 bytes, Thumb
 */

struct UnkStruct_02266f30 {
    signed char a;
    char pad_01;
    short b;
};

typedef struct {
    signed char unk_00;
    unsigned short s16;
} UnkStruct_02266e98;

typedef struct {
    unsigned int data[525];
} UnkStruct_02266e98_2;

extern int func_02091254(int, int *, int, int);
extern int func_0207dd84(int);
extern int func_020644cc(int);
extern void func_0207dd60(int);
extern int func_ov068_0226d598(int);
extern int func_020984e8(void);
extern int func_0201c330(int, int, int);
extern int func_02081edc(void *record);
extern int func_02014868(int);
extern int func_ov068_0226cc00(int);
extern int func_0201ce18(int);
extern int func_0201cddc(int);

void func_ov068_02266f40(void *object) {}

void func_ov068_02266f3c(void *object) {}

void func_ov068_02266f30(struct UnkStruct_02266f30 *p)
{
    p->a = -1;
    p->b = 0;
}

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

void func_ov068_02266e80(char *p0, void *p1)
{
    *p0 = -1;
    func_0207dd60(*(int *) ((char *) p1 + 0x830));
}

int func_ov068_02266e7c(unsigned short *p0)
{
    return p0[1];
}

void func_ov068_02266e78(unsigned short *p0, int p1)
{
    p0[1] = p1;
}

int func_ov068_02266df4(int receiver)
{
    int record;
    record = func_ov068_0226d598(receiver);
    if (func_020984e8() != 0) {
        record = func_ov068_0226d598(receiver);
    }
    if (record == 0) {
        if (func_0201c330(receiver, 0x6000, 4) == 0) {
            goto label_02266e30;
        }
    }
    if (record != 0) {
        if (func_02081edc((void *) record) != 0) {
        label_02266e30:
            if (func_02014868(receiver + 0x618) == 0) {
                if (func_ov068_0226cc00(receiver + 0x8b8) != 0) {
                    if (func_0201ce18(receiver) == 0) {
                        if (func_0201cddc(receiver) == 0xb) {
                            return 1;
                        }
                    }
                }
            }

            goto label_02266e60;
        }
    }
label_02266e60:
    return 0;
}
