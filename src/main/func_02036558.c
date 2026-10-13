/* func_02036558 @ 0x02036558, 0x8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[3];
    int unk_04;
    int unk_08;
} UnkStruct_02036558;
void func_02036558(UnkStruct_02036558 *p, int a, int b, int c)
{
    p->unk_04 = a;
    p->unk_08 = b;
    p->unk_00 = (unsigned char) c;
}
