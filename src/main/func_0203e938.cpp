/* func_0203e938 @ 0x0203e938, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203e938 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19(int, int);
};

struct UnkStruct_0203e938_2 {
    char pad_00[0x10];
    int unk_10;
    char pad_14[1];
    unsigned char unk_15;
    unsigned char unk_16;
    unsigned char unk_17;
};

extern "C" {
extern UnkStruct_0203e938 *func_0203ef90(int);
extern int func_02095d84(void);
extern int func_02095904(void);
extern void func_02095944(unsigned int);
extern int func_02095bdc(void);
extern int func_0203eda4(UnkStruct_0203e938 *);
extern void func_0203ead0(UnkStruct_0203e938 *, unsigned char);
extern void func_0203ea80(UnkStruct_0203e938_2 *, int);
extern void func_0203df6c(void);
extern unsigned char data_020dab94;
}

extern "C" int func_0203e938(UnkStruct_0203e938_2 *obj)
{
    UnkStruct_0203e938 *t;
    int r;

    t = func_0203ef90(obj->unk_10);
    switch (obj->unk_16) {
        case 0:
        case 1:
            switch (data_020dab94) {
                case 1:
                    if (obj->unk_15 == 7) {
                        obj->unk_16 = 8;
                    } else {
                        obj->unk_16 = 2;
                    }
                    break;
                case 2:
                    obj->unk_16 = 3;
                    break;
            }
            break;
    }
    if (obj->unk_16 == 8) {
        if (func_02095d84() == 0) {
            return 0;
        }
        if (func_02095904() == 0) {
            return 0;
        }
        obj->unk_16 = 2;
    }
    switch (obj->unk_16) {
        case 2:
            t->v19(3, 4);
            r = func_0203eda4(t);
            if (obj->unk_17 == 5) {
                r = 2;
            }
            if (r == 2) {
                func_02095904();
                func_0203ead0(t, obj->unk_17);
                obj->unk_16 = 5;
            } else {
                func_02095944(r);
                obj->unk_16 = 4;
            }
            return 1;
        case 3:
            if (func_02095bdc() != 0) {
                func_0203ea80(obj, 4);
                func_0203df6c();
            }
            return 0;
    }
    return 0;
}
