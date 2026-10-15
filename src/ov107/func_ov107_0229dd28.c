/* func_ov107_0229dd28 @ 0x0229dd28, 0x60 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(void *p, int v);
extern void func_ov107_0229ce90(void *p);
extern void *func_020ee45c(void *p);
extern void func_ov092_02299324(void *p, int a, int b);
extern void func_ov002_02207f04(void *p, int a, int b, int c, int d);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov002_02208090(void *p, int v);
extern int func_ov002_02207f60(void *p);

void func_ov107_0229dd28(char *p)
{
    func_ov002_02207d24(p + 0x21cc, 1);
    func_ov107_0229ce90(p);
    func_ov092_02299324(func_020ee45c(p), 0x44, 1);
    func_ov002_02207f04(p, 8, 0, 0, 0x30);
    func_ov002_02207e80(p, 6, 0, ~0xf);
    func_ov002_02208090(p, 4);
    *(int *) (p + 0x98) = func_ov002_02207f60(p);
}
