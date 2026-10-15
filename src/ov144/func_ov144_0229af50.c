/* func_ov144_0229af50 @ 0x0229af50, 0x64 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov144_0229ad24(void);
extern void func_ov144_0229ac90(void *);
extern void func_ov144_02299ea8(void *);
extern void func_ov144_0229ac40(void *);
extern void func_02002708(int);
extern void func_ov144_0229ae64(void *);
extern void func_ov144_02299670(void *, int);
extern int func_ov002_0220ab84(void *, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);

void func_ov144_0229af50(void *r0)
{
    void *r4 = r0;
    func_ov144_0229ad24();
    func_ov144_0229ac90(r4);
    func_ov144_02299ea8(r4);
    func_ov144_0229ac40(r4);
    func_ov002_02207f20(r4, 10, 4, 0, 24);
    func_02002708(6);
    func_02002708(4);
    func_ov144_0229ae64(r4);
    func_ov144_02299670(r4, 1);
    func_ov002_0220ab84((char *) r4 + 0x170, 0x65);
    func_ov002_02208090(r4, 1);
}
