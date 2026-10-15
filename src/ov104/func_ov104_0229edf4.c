/* func_ov104_0229edf4 @ 0x0229edf4, 0x60 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int v);
extern void func_ov104_0229eb68(void *p);
extern void func_ov104_0229e924(void *self);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_ov002_02207e90(void *p, int v);
extern void func_02002708(int v);
extern void func_ov104_0229c354(void *p, int v);
extern void func_ov104_0229eb48(void *p);
extern void func_ov002_02208090(void *p, int v);

void func_ov104_0229edf4(char *p)
{
    int cond = func_ov002_02207f48(p, 0);
    func_ov104_0229eb68(p);
    if (cond) {
        func_ov104_0229e924(p);
        func_ov002_02207f20(p, 2, 0, 2, 0x30);
        func_ov002_02207e90(p, 0xc0);
        func_02002708(4);
        func_ov104_0229c354(p, 0x200);
        func_ov104_0229eb48(p);
        func_ov002_02208090(p, 3);
    }
}
