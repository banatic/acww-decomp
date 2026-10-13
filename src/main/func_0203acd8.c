/* func_0203acd8 @ 0x0203acd8, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *data_021c67a4;

typedef struct {
    short unk_00;
    short unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
} SubA;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} SubB;

extern SubA data_021c6800;
extern SubB data_021c67f4;

void func_0203acd8(void)
{
    char *base = data_021c67a4;
    SubA *p = (SubA *) (base + 0xfc);
    SubB *q;
    data_021c6800.unk_00 = *(short *) (base + 0xfc);
    data_021c6800.unk_02 = p->unk_02;
    data_021c6800.unk_04 = p->unk_04;
    data_021c6800.unk_08 = p->unk_08;
    data_021c6800.unk_0C = p->unk_0C;
    data_021c6800.unk_10 = p->unk_10;
    data_021c6800.unk_14 = p->unk_14;
    data_021c6800.unk_18 = p->unk_18;
    data_021c6800.unk_1C = p->unk_1C;
    q = (SubB *) (base + 0x168);
    data_021c67f4.unk_00 = q->unk_00;
    data_021c67f4.unk_04 = q->unk_04;
    data_021c67f4.unk_08 = q->unk_08;
}
