/* func_0208a000 @ 0x0208a000, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208a000 {
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0C;
    unsigned char unk_0D;
    char pad_0E[14];
    int unk_1C;
    int unk_20;
    char pad_24[16];
    int unk_34;
};

void func_0208a000(struct UnkStruct_0208a000 *obj, int a, int b, int c, int d, int e, unsigned char f, int g)
{
    obj->unk_04 = a;
    obj->unk_08 = b;
    obj->unk_1C = c;
    obj->unk_20 = d;
    obj->unk_0C = e;
    obj->unk_0D = f;
    obj->unk_34 = g;
}
