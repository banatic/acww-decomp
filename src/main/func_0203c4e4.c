/* func_0203c4e4 @ 0x0203c4e4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xAC];
    int unk_AC;
    char pad_B0[0x0C];
    int unk_BC;
} Func0203c4e4Ctx;

extern int func_0203c4bc(Func0203c4e4Ctx *p);
extern int func_0203c528(Func0203c4e4Ctx *p);
extern int func_0203c4d0(Func0203c4e4Ctx *p);

int func_0203c4e4(Func0203c4e4Ctx *p)
{
    int a, b, c, total, sum;
    a = func_0203c4bc(p);
    b = func_0203c528(p);
    c = func_0203c4d0(p);
    total = a + (b + c);
    if (p->unk_BC < total) {
        p->unk_BC = total;
    }
    sum = p->unk_BC + p->unk_AC;
    if (sum < total) {
        return total;
    }
    return sum;
}
