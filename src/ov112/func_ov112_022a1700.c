/* func_ov112_022a1700 @ 0x022a1700, 0x58 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

void func_ov112_022a1700(unsigned char *self)
{
    extern void func_ov112_0229f078(unsigned char *);
    extern int func_ov112_0229fe70(unsigned char *, int);
    extern int func_ov002_0220aa60(unsigned char *, int);
    extern void func_ov002_02207eb4(unsigned char *, int, int);
    extern int func_ov002_02207f60(unsigned char *);
    extern void func_ov002_02208090(unsigned char *, int);

    func_ov112_0229f078(self);
    if (func_ov112_0229fe70(self, 0x2000)) {
        func_ov002_0220aa60(self + 0x427c, 0x87);
    } else {
        func_ov002_0220aa60(self + 0x427c, 0x22);
    }
    func_ov002_02207eb4(self, 5, 0);
    *(int *) (self + 0xa8) = func_ov002_02207f60(self);
    func_ov002_02208090(self, 5);
}
