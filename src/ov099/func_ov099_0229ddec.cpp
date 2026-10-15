/* func_ov099_0229ddec @ 0x0229ddec, 0x90 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229ddec {
  public:
    virtual void f0();
    virtual void f1();
    virtual int f2();
};

extern "C" void func_ov002_0220919c(void *);
extern "C" int func_ov099_0229c2ac(void *, int);
extern "C" int func_0206fe54(void);
extern "C" void func_ov002_02209eb8(void *);
extern "C" void func_ov099_0229c994(void *);
extern "C" void func_ov094_0229a850(void *, int, int);
extern "C" void func_ov094_0229b738(void *, int, int);
extern "C" void func_ov094_02299d84(void *receiver, int value);

extern "C" int func_ov099_0229ddec(void *p)
{
    func_ov002_0220919c((char *) p + 0x22d8);
    if (func_ov099_0229c2ac(p, 1) == 0) {
        return 1;
    }

    UnkStruct_0229ddec *obj = (UnkStruct_0229ddec *) ((char *) p + 0x218c);
    obj->f2();
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8((char *) p + 0x2274);
    }

    func_ov099_0229c994(p);

    if (func_ov099_0229c2ac(p, 2) != 0) {
        func_ov094_0229a850((char *) p + 0xcc, 0, *(int *) ((char *) p + 0x27ec));
        func_ov094_0229b738((char *) p + 0xb2c, 0, *(int *) ((char *) p + 0x27ec));
        func_ov094_02299d84((char *) p + 0xb54, *(int *) ((char *) p + 0x27ec));
    }

    return 1;
}
