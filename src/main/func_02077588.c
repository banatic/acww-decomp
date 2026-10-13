/* func_02077588 @ 0x02077588, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020779b8(int, int, int);

struct UnkStruct_02077588 {
    int unk_00;
    int unk_04;
    int unk_08;
};

void func_02077588(int a, struct UnkStruct_02077588 *s)
{
    func_020779b8(a, s->unk_00, s->unk_08);
}
