/* func_ov068_02269b38 @ 0x02269b38, 0x50 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(int);
extern int func_02019de8(int);
extern void func_0201cc48(void *);
extern void *func_0201ce50(void *);

typedef struct {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
    unsigned char pad_1D[0x0b];
    int unk_28;
} UnkStruct_02269b38;

void func_ov068_02269b38(UnkStruct_02269b38 *p, void *q)
{
    if (func_02019e00(p->unk_28 + 0x564) != 20) {
        return;
    }
    if (func_02019de8(p->unk_28 + 0x564) == 0) {
        return;
    }
    func_0201cc48((char *) q + 0x83c);
    func_0201cc48((char *) func_0201ce50(q) + 0x83c);
    p->unk_1C = 3;
}
