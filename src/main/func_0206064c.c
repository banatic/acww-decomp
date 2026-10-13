/* func_0206064c @ 0x0206064c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206052c(void *g, int p1, void *p2);
extern void func_020605ac(void *g, int p1, unsigned p2);
extern int func_020606fc(void *g, int p1);
extern void func_02060588(void *g, int p1);
extern int func_020606d4(void *g, int p1);
extern void func_020554b0(int a, int b);

extern int data_021cad80;

typedef struct {
    char c;
    int unk_04;
    char pad_08[32];
    int unk_28;
} UnkStruct_0206064c;

void func_0206064c(UnkStruct_0206064c *p0, int p1, int p2, unsigned p3)
{
    int res_fc;
    int res_d4;

    p0->c = p1;
    if (p3 < 3) {
        func_0206052c(&data_021cad80, p1, p0);
        func_020605ac(&data_021cad80, p1, p3);
    } else {
        func_0206052c(&data_021cad80, p1, 0);
        func_020605ac(&data_021cad80, p1, 0);
    }
    res_fc = func_020606fc(&data_021cad80, p1);
    func_02060588(&data_021cad80, p1);
    res_d4 = func_020606d4(&data_021cad80, p1);
    func_020554b0(res_d4, res_fc);
    if (p2 != 0) {
        p0->unk_28 = p2;
    }
    p0->unk_04 = 0;
}
