/* func_020bbdc8 @ 0x020bbdc8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    char pad0[0x28];
    int field_0x28;
    char pad1[8];
    int field_0x34;
} data_021f8ab0;

extern void func_020e88dc(int *ptr, int a, int b);

typedef struct {
    char pad_00[0x0c];
    int unk_0C;
} Param;

void func_020bbdc8(Param *p)
{
    int v_28;
    int v_3;
    int v_4;
    int v_34_is1;
    int r1;
    int r2;

    v_28 = data_021f8ab0.field_0x28;
    v_3 = (v_28 == 3) ? 1 : 0;
    v_4 = (v_28 == 4) ? 1 : 0;
    v_34_is1 = (data_021f8ab0.field_0x34 == 1) ? 1 : 0;
    r1 = 0;
    if (v_34_is1) {
        if (v_3) {
            r1 = 0x099a00;
        } else if (v_4) {
            r1 = 0x100000;
        }
    }
    r2 = 0xdf;
    if (v_34_is1) {
        if (r1 < p->unk_0C) {
            r2 = 0x1eb;
        }
    } else {
        r2 = 0x5200;
    }
    func_020e88dc(&p->unk_0C, r1, r2);
}
