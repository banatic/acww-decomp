/* func_ov003_022118d8 @ 0x022118d8, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020778b0(void *, int);

typedef struct {
    unsigned short head;
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned char unk_04;
} UnkStruct_022118d8;

typedef struct {
    int unk_00;
    int unk_04;
} In;

void func_ov003_022118d8(UnkStruct_022118d8 *out, In *in, int x, int y)
{
    out->unk_02 = in->unk_00;
    out->unk_03 = in->unk_04;
    func_020778b0(out, x);
    out->unk_04 = y;
}
