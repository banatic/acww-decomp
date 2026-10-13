/* func_ov126_022a19d8 @ 0x022a19d8, 0x60 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002708(int);
extern void func_ov126_022a12d4(void *);
extern void func_ov126_022a0168(void *);
extern void func_ov126_022a0054(void *);
extern void func_ov126_022a16ac(void *);
extern void func_ov126_0229f7b8(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov095_0229c420(void *, int);

void func_ov126_022a19d8(void *r4)
{
    func_ov095_0229c420((char *) r4 + 0x19c, 6);
    func_ov126_022a12d4(r4);
    func_ov126_022a0168(r4);
    func_ov126_022a0054(r4);
    func_ov002_02207f20(r4, 0xa, 4, 0, 0x30);
    func_02002708(4);
    func_02002708(6);
    func_ov126_022a16ac(r4);
    func_ov126_0229f7b8(r4, 1);
    func_ov002_02208090(r4, 2);
}
