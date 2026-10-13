/* func_020bd7a4 @ 0x020bd7a4, 0x194 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020bd7a4 UnkStruct_020bd7a4;

extern void func_020bdc50(UnkStruct_020bd7a4 *p, int a, int b, int c, int d);
extern int func_020644cc(int arg);
extern int data_021f8ab0[];

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020bd7a4_2;

extern UnkStruct_020bd7a4_2 data_020d2424[];

struct UnkStruct_020bd7a4 {
    char pad_00[0x2f00];
    int unk_2F00;
    int unk_2F04;
    int unk_2F08;
    int unk_2F0C;
};

void func_020bd7a4(UnkStruct_020bd7a4 *p)
{
    int mode;
    int a;
    int b;
    UnkStruct_020bd7a4_2 *e;

    mode = 0;
    a = data_021f8ab0[9];
    b = data_021f8ab0[10];
    if (a == b) {
        if (a == 3) {
            mode = 2;
        } else if (a == 4) {
            mode = 4;
        }
    } else if (a > b) {
        if (b == 3) {
            mode = 3;
        } else if (b <= 3) {
            mode = 1;
        }
    } else {
        if (b == 3) {
            mode = 1;
        } else if (b > 3) {
            mode = 3;
        }
    }

    if (mode == 0) {
        p->unk_2F00 = 0;
        p->unk_2F0C = 0;
        return;
    }

    e = &data_020d2424[mode - 1];
    if (p->unk_2F00 == 0) {
        p->unk_2F00 = 1000;
    }

    if (p->unk_2F0C > 2) {
        if (b >= 3) {
            p->unk_2F08 = p->unk_2F08 + 2;
            if (p->unk_2F08 > 0x6400) {
                p->unk_2F08 = 0x6400;
            }
        } else {
            p->unk_2F08 = p->unk_2F08 - 2;
            if (p->unk_2F08 < 0) {
                p->unk_2F08 = 0;
            }
        }
    } else {
        if (b >= 3) {
            p->unk_2F08 = 0x6400;
        } else {
            p->unk_2F08 = p->unk_2F08 - 2;
            if (p->unk_2F08 < 0) {
                p->unk_2F08 = 0;
            }
        }
    }

    p->unk_2F04 = p->unk_2F04 + (p->unk_2F08 >> 8);

    while (p->unk_2F04 >= p->unk_2F00) {
        func_020bdc50(p, 1, 0x3c, 0, 0);
        p->unk_2F04 = p->unk_2F04 - p->unk_2F00;
        if (p->unk_2F04 <= p->unk_2F00) {
            switch (p->unk_2F0C) {
                case 0:
                    p->unk_2F00 = 0x2af8;
                    p->unk_2F04 = 0;
                    break;
                case 1:
                    p->unk_2F00 = 0x2328;
                    p->unk_2F04 = 0;
                    break;
                default:
                    p->unk_2F00 = e->unk_00 + func_020644cc(e->unk_04);
                    if (p->unk_2F0C < 0x32) {
                        p->unk_2F04 = 0x4b;
                    } else {
                        p->unk_2F04 = 0;
                    }
                    break;
            }
            p->unk_2F0C = p->unk_2F0C + 1;
            if (p->unk_2F0C > 0x32) {
                p->unk_2F0C = 0x32;
            }
            break;
        }
    }
}
