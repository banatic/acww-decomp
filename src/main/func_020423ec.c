/* func_020423ec @ 0x020423ec, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02042418(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);

typedef struct {
    char pad_00[0x20];
    unsigned int unk_20;
} UnkStruct_020423ec;

extern UnkStruct_020423ec data_021c779c;

void func_020423ec(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    unsigned int val;
    val = data_021c779c.unk_20;
    if (val != 0) {
        func_02042418(val, a, b, c, d);
    }
}
