/* func_ov134_022996b4 @ 0x022996b4, 0x5c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

struct St {
    int unk_00;
    int unk_04;
};
extern int func_ov134_022995c0(struct St *p, unsigned int mask);
extern void func_ov134_0229a1d8(struct St *p, int a);
extern void func_ov134_02299a3c(struct St *p);

void func_ov134_022996b4(struct St *p)
{
    int a;
    int b;

    if (func_ov134_022995c0(p, 1) != 0) {
        return;
    }
    a = p->unk_00;
    b = p->unk_04;
    if (b > 0) {
        if (b < 8) {
            a += b;
            p->unk_04 = 0;
        } else {
            a += 8;
            b -= 8;
            p->unk_04 = b;
        }
    } else if (b < 0) {
        if (b > -8) {
            a += b;
            p->unk_04 = 0;
        } else {
            a -= 8;
            b += 8;
            p->unk_04 = b;
        }
    }
    if (a != p->unk_00) {
        func_ov134_0229a1d8(p, a);
        func_ov134_02299a3c(p);
    }
}
