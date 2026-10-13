/* func_ov147_02299d20 @ 0x02299d20, 0x2c bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

struct Unk_02299d20 {
    int unk_00;
    int unk_04;
};

extern struct Unk_02299d20 *func_020682e0(int a);
extern void func_02068320(struct Unk_02299d20 *p);
extern void func_ov147_02299fc8(char *p, int a);
extern void func_ov147_0229a630(char *p, int a);

void func_ov147_02299d20(char *self)
{
    struct Unk_02299d20 *p;

    p = func_020682e0(0);
    if (p->unk_04 != 0) {
        return;
    }
    func_02068320(p);
    func_ov147_02299fc8(self, 0);
    self += 0xb0;
    func_ov147_0229a630(self, 1);
}
