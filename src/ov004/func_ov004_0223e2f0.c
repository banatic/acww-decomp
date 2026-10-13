/* func_ov004_0223e2f0 @ 0x0223e2f0, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov004_022561a4[], data_ov004_02256274[];
extern void *data_021fbe94;
extern int func_0205556c(void *, unsigned int, void *);
extern void *func_020e99d8(int, void *);
extern void func_020ee4cc(void *, void *);
extern int func_02055140(void *, void *);
extern void *func_02064b18(void *);
extern int func_020e9abc(void *);
extern void func_020e9974(void);
extern void *NNS_G3dGetVisAnmSet(void *);
extern void *func_02107cf0(void *, int);
extern void func_02055060(void *, void *, int, int, unsigned short, unsigned short);
extern void func_02055050(void *);
extern void func_0200430c(void *);
int func_ov004_0223e2f0(unsigned char *self)
{
    void *heap, *resource;
    short *angle;
    func_0205556c(self + 0x120, 0x474f4b49, data_ov004_022561a4);
    heap = func_020e99d8(0x5000, data_021fbe94);
    func_020ee4cc(self, heap);
    func_02055140(self + 0x120, 0);
    resource = func_02064b18(data_ov004_02256274);
    func_020e9abc(heap);
    func_020e9974();
    func_02055060(self + 0x120, func_02107cf0(NNS_G3dGetVisAnmSet(resource), 0), 0, 0x1000, 0, 0);
    func_02055050(self + 0x120);
    func_0200430c(self + 0x114);
    angle = (short *) (self + 0x92);
    angle[1] = *(short *) (self + 0x8e);
    *(short *) (self + 0x228) = angle[1];
    *(int *) (self + 0x9c) = -0x333;
    *(int *) (self + 0x98) = *(int *) (self + 0xd4);
    self[0x22a] = 0;
    self[0x263] = 0;
    *(int *) (self + 0x264) = 0;
    return 1;
}
