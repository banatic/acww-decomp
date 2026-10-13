/* func_ov003_0220fb14 @ 0x0220fb14, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0220fb14 {
    int unk_00;
    int unk_04;
    unsigned short unk_08;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
};

void func_ov003_0220fb14(struct UnkStruct_0220fb14 *out, int a, int b, int c, unsigned char d, unsigned char e)
{
    out->unk_08 = a;
    out->unk_00 = b;
    out->unk_04 = c;
    out->unk_0B = d;
    out->unk_0C = e;
    out->unk_0A = 0;
}
