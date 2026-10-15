/* func_ov100_0229e5b8 @ 0x0229e5b8, 0x74 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229c2d8(void *);
extern int func_ov002_02207d24(void *, int);
extern void func_ov100_0229cc3c(void *);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02207e90(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);
extern void func_ov002_02208090(void *, int);

void func_ov100_0229e5b8(void *param)
{
    if (func_ov100_0229c2d8(param) == 0) {
        return;
    }
    func_ov002_02207d24((char *) param + 0x218c, 1);
    func_ov100_0229cc3c(param);
    func_ov092_02299324(func_020ee45c(param), 0x44, 1);
    func_ov002_02207f04(param, 2, 4, 1, 0x30);
    func_ov002_02207e90(param, 0x80);
    func_ov002_02207e80(param, 4, 0, 0);
    *((int *) ((char *) param + 0x28c8)) = func_ov002_02207f60(param);
    func_ov002_02208090(param, 5);
}
