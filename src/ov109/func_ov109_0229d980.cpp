/* func_ov109_0229d980 @ 0x0229d980, 0xa4 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern void func_ov002_0220919c(void *);
extern int func_ov109_0229c2ac(void *, int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern void func_ov109_0229c8f8(void *);
extern void func_ov002_0220ad18(void *, int);
extern void func_ov094_0229a850(void *, int, int);
extern void func_ov094_0229b738(void *, int, int);
extern void func_ov094_02299d84(void *receiver, int value);
}

class UnkStruct_0229d980 {
  public:
    virtual void f0();
    virtual void f1();
    virtual int f2();
};

extern "C" int func_ov109_0229d980(void *p)
{
    func_ov002_0220919c((char *) p + 0x22d8);
    if (func_ov109_0229c2ac(p, 1) == 0) {
        return 1;
    }
    ((UnkStruct_0229d980 *) ((char *) p + 0x218c))->f2();
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8((char *) p + 0x2274);
    }
    func_ov109_0229c8f8(p);
    if (func_ov109_0229c2ac(p, 2) != 0) {
        func_ov002_0220ad18((char *) p + 0x27e8, *(int *) ((char *) p + 0x29b8));
        int r4 = *(int *) ((char *) p + 0x29b8) - 0x10;
        func_ov094_0229a850((char *) p + 0xcc, 0, r4);
        func_ov094_0229b738((char *) p + 0xb2c, 0, r4);
        func_ov094_02299d84((char *) p + 0xb54, r4);
    }
    return 1;
}
