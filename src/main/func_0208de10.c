/* func_0208de10 @ 0x0208de10, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a1d0(void *);
extern int func_0208a1b0(void *, int);
extern int func_0208a198(void *, int);
extern int func_0208aef0(void *);
extern int func_0208aeec(void *);
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);

typedef struct {
    char pad_00[0x0c];
    int sub;
    char pad_10[0x10];
    int flag32;
    char pad_24[0x2c];
    int unk_50;
    char pad_54[0x10];
    int unk_64;
} UnkStruct_0208de10;

void func_0208de10(UnkStruct_0208de10 *p)
{
    int ret1, ret2, ret3, ret4, r4_calc, r3_calc, tmp;
    int arg5;
    if (p->flag32 == 0) {
        return;
    }
    ret1 = func_0208a1d0(&p->sub);
    if (ret1 == 0) {
        return;
    }
    ret2 = func_0208a1b0(&p->sub, -1);
    ret3 = func_0208a198(&p->sub, -1);
    ret4 = func_0208aef0(p);
    r4_calc = (p->unk_50 + 0x800) >> 12;
    tmp = func_0208aeec(p);
    r3_calc = tmp + r4_calc;
    if (p->unk_64 == 0) {
        arg5 = 15;
    } else {
        arg5 = 9;
    }
    func_02088df8(0, ret1, ret4 + ret2, r3_calc + ret3, arg5, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
