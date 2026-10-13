/* func_020330bc @ 0x020330bc, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct InputStruct {
    int unk_00;
    int pad_04;
    int unk_08;
};

struct OutputStruct {
    char pad_00[0x14];
    char sub[0x8];
    int unk_1C;
    short unk_20;
    short unk_22;
};

void func_02030640(struct OutputStruct *out, struct InputStruct *in, int p3, int p4);
void func_0203428c(void *ptr, int arg, int arg2);

void func_020330bc(struct OutputStruct *out, struct InputStruct *in, int p3, int p4, int p5, int p6)
{
    int t1 = in->unk_08 >> 13;
    int t2 = in->unk_00 >> 13;
    out->unk_20 = t2;
    out->unk_22 = t1;

    func_02030640(out, in, p3, p4);

    out->unk_1C = p5;

    func_0203428c(out->sub, p6, 0);
}
