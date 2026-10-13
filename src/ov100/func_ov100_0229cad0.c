/* func_ov100_0229cad0 @ 0x0229cad0, 0x4c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(char *);
extern int func_ov002_02208ad8(char *, unsigned char);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_ov002_0220a374(char *, int);

void func_ov100_0229cad0(unsigned char *self)
{
    int v1;
    int v2;
    self[0x2926] = 0;
    v1 = func_ov002_02208ae4((char *) (self + 0x22d8));
    v2 = func_ov002_02208ad8((char *) (self + 0x22d8), self[0x2926]);
    func_ov002_0220a0b4((char *) (self + 0x2274), v1, v2);
    func_ov002_0220a374((char *) (self + 0x2274), 7);
}
