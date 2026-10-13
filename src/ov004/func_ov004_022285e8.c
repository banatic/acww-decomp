/* func_ov004_022285e8 @ 0x022285e8, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020779b8(void *s, int a, int b);
extern void func_02077910(char *p, short d);

struct UnkStruct_022285e8 {
    char data[5];
    char unk_05;
    char unk_06;
    char unk_07;
};

void func_ov004_022285e8(struct UnkStruct_022285e8 *s, char v, int a, int b, short d)
{
    s->unk_07 = v;
    func_020779b8(s, a, b);
    func_02077910(&s->unk_05, d);
}
