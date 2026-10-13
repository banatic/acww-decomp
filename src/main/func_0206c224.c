/* func_0206c224 @ 0x0206c224, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206c278(int, unsigned int, unsigned int);

struct UnkStruct_0206c224 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
};

void func_0206c224(int a, struct UnkStruct_0206c224 *s)
{
    func_0206c278(a, s->unk_10, s->unk_08 + 6);
}
