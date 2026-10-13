/* func_ov134_0229b884 @ 0x0229b884, 0xc bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229b848(void *p1, int p2, void *p3);

struct S_0229b884 {
    char pad_00[0xb8];
    int unk_B8;
};

void func_ov134_0229b884(struct S_0229b884 *s, int b)
{
    func_ov134_0229b848(s, b, &s->unk_B8);
}
