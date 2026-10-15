/* func_ov146_0229ae90 @ 0x0229ae90, 0x66 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov146_0229abe0(void);
extern void func_ov146_0229ab28(void *);
extern int func_ov146_02299f08(void *);
extern void func_ov146_02299dec(void *, int);
extern void func_ov146_0229aac8(void *receiver);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov146_0229adb8(void *);
extern void func_ov146_02299660(void *, int);
extern void func_ov002_02208090(void *, int);

void func_ov146_0229ae90(void *r0)
{
    void *r4 = r0;
    int sp0;
    int sp4;

    func_ov146_0229abe0();
    func_ov146_0229ab28(r4);
    func_ov146_02299f08(r4);
    func_ov146_02299dec(r4, 0);
    *(int *) ((char *) r4 + 0xa8) = 0;
    func_ov146_0229aac8(r4);
    sp0 = 0x28;
    func_ov002_02207f20(r4, 0xa, 4, 0, sp0);
    func_02002708(6);
    func_02002708(4);
    func_ov146_0229adb8(r4);
    func_ov146_02299660(r4, 1);
    func_ov002_02208090(r4, 1);
}
