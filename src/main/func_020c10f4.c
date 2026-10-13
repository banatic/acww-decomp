/* func_020c10f4 @ 0x020c10f4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d23ec[];
extern int data_020d26f0;
extern int func_020c1144(void *);

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    char pad_10[0x3c];
    int unk_4C;
    int unk_50;
    char pad_54[0x4];
    int unk_58;
    char pad_5C[0x4];
    int unk_60;
    int unk_64;
} UnkStruct_020c10f4;

void func_020c10f4(UnkStruct_020c10f4 *p, int param)
{
    int x = param & 0xf;
    int v;

    p->unk_0C = data_020d23ec[x];

    if (x == 1) {
        p->unk_58 = 3;
    } else {
        p->unk_58 = 2;
    }

    p->unk_60 = param;
    p->unk_64 = 0;

    if (x == 1) {
        v = data_020d26f0;
        p->unk_4C = v;
        p->unk_50 = v;
        if (func_020c1144(p) == 0) {
            p->unk_04 = 3;
        }
    }
}
