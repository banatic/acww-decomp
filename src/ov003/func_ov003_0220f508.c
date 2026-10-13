/* func_ov003_0220f508 @ 0x0220f508, 0x1a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077950(int a, int b, int c, int d, int e);

struct S_22f508 {
    int unk_00;
    int unk_04;
    int unk_08;
};

int func_ov003_0220f508(int a, struct S_22f508 *p)
{
    return func_02077950(a, p->unk_00, p->unk_04, p->unk_08, 0);
}
