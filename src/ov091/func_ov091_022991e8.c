/* func_ov091_022991e8 @ 0x022991e8, 0x5c bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(unsigned char *, int);
extern unsigned char *func_ov002_022080a0(unsigned char *, unsigned char value);
extern void func_ov002_0220a374(unsigned char *, int);
extern int func_0206fe60(void);
extern unsigned char *func_ov002_02208098(unsigned char *, unsigned char value);
extern void func_ov002_02207e80(unsigned char *, int, int, int);

void func_ov091_022991e8(unsigned char *self)
{
    if (func_ov002_02207f48(self, 1) != 0) {
        func_ov002_022080a0(self, 2);
        func_ov002_0220a374(self + 0x434, 1);
        if (func_0206fe60() != 0) {
            func_ov002_02208098(self, 0);
        } else {
            func_ov002_02208098(self, 1);
        }
    }
    func_ov002_02207e80(self, 0, 0, 0);
    func_ov002_02207e80(self, 2, 0, 0);
}
