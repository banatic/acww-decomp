/* func_ov125_022a0664 @ 0x022a0664, 0x60 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022097b8(void *);
extern void func_ov125_022a0334(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern int func_ov125_022a0564(void *);
extern int func_ov002_0220ab84(void *, int);
extern void func_ov125_0229f75c(void *, int);
extern void func_ov002_02208090(void *, int);

void func_ov125_022a0664(void *arg0)
{
    void *r4 = arg0;
    func_ov002_022097b8((char *) r4 + 0x180);
    func_ov125_022a0334(r4);
    func_ov002_02207f20(r4, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov125_022a0564(r4);
    func_ov002_0220ab84((char *) r4 + 0x6a8, 0x65);
    func_ov125_0229f75c(r4, 1);
    func_ov002_02208090(r4, 2);
}
