/* func_ov104_0229ed6c @ 0x0229ed6c, 0x60 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int v);
extern void func_ov104_0229d378(void *p);
extern int func_ov104_0229c364(void *p, int v);
extern void *func_020ee45c(void *p);
extern void func_ov092_02299324(void *p, int a, int b);
extern void func_ov002_02207f04(void *p, int a, int b, int c, int d);
extern void func_ov002_02207e90(void *p, int v);
extern void func_ov002_02208090(void *p, int v);

void func_ov104_0229ed6c(char *p)
{
    func_ov002_02207d24(p + 0x23b8, 1);
    func_ov104_0229d378(p);
    if (!func_ov104_0229c364(p, 0x100)) {
        func_ov092_02299324(func_020ee45c(p), 0x44, 1);
    }
    func_ov002_02207f04(p, 2, 0, 2, 0x30);
    func_ov002_02207e90(p, 0xc0);
    func_ov002_02208090(p, 5);
}
