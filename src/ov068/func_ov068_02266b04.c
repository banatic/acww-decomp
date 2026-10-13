/* func_ov068_02266b04 @ 0x02266b04, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int data_020c814c;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    short unk_14;
} UnkStruct_02266b04;

void func_ov068_02266be4(UnkStruct_02266b04 *p, int a, int b, int c, int d, int e, int f, int data_020c814c, int h);

void func_ov068_02266b04(UnkStruct_02266b04 *p, int a, int b, int c, int d)
{
    p->unk_0C = b;
    p->unk_10 = c;
    func_ov068_02266be4(p, a, 3, 0, 0, d, 4, data_020c814c, 1);
    p->unk_04 = 0;
    p->unk_14 = 0;
}
