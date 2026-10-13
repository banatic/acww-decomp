/* func_02067e84 @ 0x02067e84, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02067e84 {
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
    virtual void v24();
    virtual void v25();
    virtual int v26();
};

struct UnkStruct_02067e84_2 {
    char pad_00[0x14a8];
    UnkStruct_02067e84 *unk_14A8;
};

extern "C" {
extern int func_020668c8(UnkStruct_02067e84 *);
extern void *G2_GetBG2ScrPtr(void);
extern void func_020675c0(UnkStruct_02067e84_2 *);
extern void func_020675e0(UnkStruct_02067e84_2 *);
extern unsigned short data_020ccf50;
extern unsigned short data_020ccf54;
extern unsigned short data_020ccf58;
}

extern "C" void func_02067e84(UnkStruct_02067e84_2 *obj)
{
    int flag;
    int mode;
    unsigned short *base;
    unsigned short *q;
    int y;
    int x;
    unsigned short v;
    unsigned short g0;
    unsigned short g1;
    unsigned short g2;

    if (obj->unk_14A8->v26() == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    mode = func_020668c8(obj->unk_14A8);
    base = (unsigned short *) G2_GetBG2ScrPtr();
    y = 0xd;
    g0 = data_020ccf50;
    g1 = data_020ccf54;
    g2 = data_020ccf58;
    for (; y <= 0x10; y++) {
        unsigned short *row;
        x = 3;
        row = (unsigned short *) ((char *) base + (y << 6));
        for (; x <= 0xe; x++) {
            q = &row[x];
            v = (unsigned short) (row[x] & ~0xf000);
            if (flag != 0) {
                v |= g0;
            } else if (mode == 1) {
                v |= g1;
            } else {
                v |= g2;
            }
            *q = v;
        }
    }
    func_020675c0(obj);
    func_020675e0(obj);
}
