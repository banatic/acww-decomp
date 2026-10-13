/* func_0209d3f8 @ 0x0209d3f8, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern void *data_020ccf94;
extern unsigned char data_020e54a8;
extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
}
struct UnkStruct_0209d3f8 {
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
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual int slot(unsigned char);
    char pad_04[0xe6];
    unsigned char unk_EA;
};
struct Bits {
    unsigned char lo : 4;
    unsigned char hi : 4;
};
extern "C" int func_0209d3f8(UnkStruct_0209d3f8 *obj, unsigned char a1)
{
    Bits b;
    void *ptr;
    unsigned char v;
    unsigned int ok;
    if (data_020e54a8 == 1) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok != 0) {
        if (obj->slot(a1) != 0) {
            v = obj->unk_EA;
            if (v < 3) {
                if (func_02073d90(data_020ccf94) != 0) {
                    b.lo = v;
                    b.hi = a1;
                    ptr = data_020ccf94;
                    func_02073820(ptr);
                    func_020737f0(ptr, &b, 1);
                    func_02073770(ptr, 0x25, 4);
                }
            }
            return 1;
        }
    }
    return 0;
}
