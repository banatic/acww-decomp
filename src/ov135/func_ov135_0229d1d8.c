/* func_ov135_0229d1d8 @ 0x0229d1d8, 0x5a bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov135_0229d030(void);
extern void func_ov135_0229d010(void *);
extern void func_ov135_0229cff0(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov135_0229d128(void *);
extern void func_ov135_0229c564(void *, int);
extern int func_ov002_0220ab38(char *, int);
extern void func_ov002_02208090(void *, int);

void func_ov135_0229d1d8(void *p)
{
    func_ov135_0229d030();
    func_ov135_0229d010(p);
    func_ov135_0229cff0(p);
    func_ov002_02207f20(p, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov135_0229d128(p);
    func_ov135_0229c564(p, 1);
    func_ov002_0220ab38((char *) p + 0xfc, 0x65);
    func_ov002_02208090(p, 1);
}
