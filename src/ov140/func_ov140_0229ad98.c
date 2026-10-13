/* func_ov140_0229ad98 @ 0x0229ad98, 0x38 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov140_0229ad4c(void *);
extern void func_ov002_02208090(void *, int);

void func_ov140_0229ad98(void *arg)
{
    int v = func_020ee45c(arg);
    func_ov092_02299324(v, 0x44, 1);
    func_ov002_02207f04(arg, 8, 0, 0, 0x30);
    func_ov140_0229ad4c(arg);
    func_ov002_02208090(arg, 4);
}
