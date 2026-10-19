/* func_ov125_0229fe58 @ 0x0229fe58, 0x40 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov125_0229f75c(unsigned short *object, unsigned short mask);

extern void func_ov125_0229faf8(void *);
extern void func_0206fc4c(int);
extern int func_ov002_02207d24(void *, int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern void func_0200467c(int);

void func_ov125_0229fe58(void *arg0)
{
    void *r4 = arg0;
    func_ov125_0229faf8(r4);
    func_ov002_02207d24((char *) r4 + 0x574, 1);
    func_ov125_0229f75c(r4, 0x10);
    *(unsigned char *) ((char *) r4 + 0x8c) = 3;
    func_0206fc4c(0);
    func_ov002_022080a0(r4, 1);
    func_0200467c(0x28);
}
