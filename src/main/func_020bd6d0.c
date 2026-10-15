/* func_020bd6d0 @ 0x020bd6d0, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020bd6d0 UnkStruct_020bd6d0;

extern int func_020be0d4(UnkStruct_020bd6d0 *p, int arg);
extern void *func_020bdc50(UnkStruct_020bd6d0 *p, int a, int b, int c, int d);
extern int func_020644cc(int arg);
extern int data_021f8ab0[];
extern unsigned char data_021f3b28[];

struct UnkStruct_020bd6d0 {
    char pad_00[0x2f19];
    unsigned char unk_2F19;
    char pad_2F1A[2];
    int unk_2F1C;
    int unk_2F20;
    char pad_2F24[8];
    int unk_2F2C;
    char pad_2F30[0x1c];
    int unk_2F4C;
};

void func_020bd6d0(UnkStruct_020bd6d0 *p)
{
    unsigned char s1;
    int s2;
    int r4;
    int r6;
    int r7;

    s1 = p->unk_2F19;
    r4 = 1;
    if (s1 < 0x13 && s1 >= 4) {
        r4 = 0;
    }

    s2 = data_021f8ab0[9];
    r6 = 0;
    if (s2 != 3 && s2 != 4) {
        r6 = 1;
    }

    r7 = 0;
    if (p->unk_2F2C == 0) {
        if (func_020be0d4(p, 9) == 0x3c) {
            r7 = 1;
        }
    }

    if (r4 != 0 && r6 != 0 && r7 != 0) {
        if (p->unk_2F4C > 0) {
            p->unk_2F4C = p->unk_2F4C - 1;
            if (p->unk_2F4C == 0) {
                func_020bdc50(p, 3, 0x1e, 0, 0);
            }
        } else {
            if (p->unk_2F1C == 0x1e && p->unk_2F1C != p->unk_2F20) {
                int arg = (data_021f3b28[2] == 0) ? 4 : 0x100;
                if (func_020644cc(arg) == 0) {
                    p->unk_2F4C = func_020644cc(0x258);
                }
            }
        }
    } else {
        p->unk_2F4C = 0;
    }
}
