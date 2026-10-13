/* func_02017f1c @ 0x02017f1c, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02017f1c {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void doit(void *other, unsigned char flag);
};

extern "C" {
extern int func_020164a0(void *p, int x);
extern int func_020164cc(void *p, void *q);
extern void func_02016764(void *a, void *b, int c, unsigned short d, int e, int f, int g, int h);
extern void func_02012444(int a, unsigned short b, int c);
extern void func_020912d4(int a, void *b, void *c, int d);
extern volatile unsigned short data_020c80f8;

int func_02017f1c(int unused, UnkStruct_02017f1c *arg1, void *arg2, int check, unsigned char flag)
{
    if (check == func_020164a0((char *) arg1 + 0x334, 0)) {
        if (func_020164cc((char *) arg1 + 0x334, arg1) != 0) {
            unsigned short w = data_020c80f8;
            int p;
            func_02016764((char *) arg1 + 0x334, arg1, 0, data_020c80f8, 0, 0x1000, 0, 0);
            p = *(int *) ((char *) arg1 + 0x628);
            if (p != 0) {
                func_02012444(p, w, 0);
            }
            return 1;
        } else {
            unsigned int v = (*(unsigned int *) ((char *) arg1 + 0x190) << 4) >> 16;
            switch (v) {
                case 8:
                    arg1->doit(arg2, flag);
                    break;
                case 0xd:
                    func_020912d4(0x22, (char *) arg1 + 0x5c, 0, 0);
                    break;
                case 3: {
                    signed short val = *(signed short *) ((char *) arg1 + 0x8e);
                    func_020912d4(0x28, (char *) arg1 + 0x490, &val, 0);
                    func_020912d4(0x28, (char *) arg1 + 0x484, &val, 0);
                    break;
                }
            }
        }
    }
    return 0;
}
}
