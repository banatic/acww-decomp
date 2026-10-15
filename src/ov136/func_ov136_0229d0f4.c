/* func_ov136_0229d0f4 @ 0x0229d0f4, 0x5a bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov136_0229cf54(void);
extern void func_ov136_0229cf34(void *);
extern void func_ov136_0229cf14(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov136_0229d044(void *);
extern void func_ov136_0229c564(void *, int);
extern int func_ov002_0220ab84(void *, int);
extern void func_ov002_02208090(void *, int);

void func_ov136_0229d0f4(void *p)
{
    func_ov136_0229cf54();
    func_ov136_0229cf34(p);
    func_ov136_0229cf14(p);
    func_ov002_02207f20(p, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov136_0229d044(p);
    func_ov136_0229c564(p, 1);
    func_ov002_0220ab84((char *) p + 0xf8, 0x21);
    func_ov002_02208090(p, 1);
}
