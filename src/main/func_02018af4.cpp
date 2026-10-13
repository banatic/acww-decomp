/* func_02018af4 @ 0x02018af4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int func_020164cc(void *);
extern void func_02016764(void *, void *, int, unsigned short, int, int, int, int);
extern void func_02012444(void *, unsigned short, int);
extern volatile unsigned short data_020c80f8;
}

class UnkStruct_02018af4 {
  public:
    virtual int v0() = 0;
    virtual int v1() = 0;
    virtual int v2() = 0;
    virtual int v3() = 0;
    virtual int v4() = 0;
    virtual int v5() = 0;
    virtual int v6() = 0;
    virtual int v7() = 0;
    virtual int v8() = 0;
    virtual int v9() = 0;
    virtual int v10() = 0;
    virtual int v11() = 0;
    virtual int v12() = 0;
    virtual int v13() = 0;
    virtual int v14() = 0;
    virtual int v15() = 0;
    virtual int v16() = 0;
    virtual int v17() = 0;
    virtual int v18() = 0;
    virtual int v19() = 0;
    virtual int v20() = 0;
    virtual int v21() = 0;
    virtual int v22() = 0;
    virtual int v23() = 0;
    virtual int v24() = 0;
    virtual int v25() = 0;
    virtual int v26() = 0;
    virtual int v27() = 0;
    virtual int v28() = 0;
    virtual int v29() = 0;
    virtual int v30() = 0;
    virtual int v31() = 0;
    virtual int v32() = 0;
    virtual int v33() = 0;
    virtual int v34() = 0;
    virtual int v35() = 0;
    virtual int v36() = 0;
    virtual int v37() = 0;
    virtual int v38() = 0;
    char pad_04[0x624];
    void *unk_628;
};

extern "C" void func_02018af4(char *param0, UnkStruct_02018af4 *param1)
{
    if (func_020164cc((char *) param1 + 0x334) != 0) {
        int ret = param1->v38();
        unsigned short g = data_020c80f8;
        func_02016764((char *) param1 + 0x334, param1, ret, data_020c80f8, 0, 0x1000, 0, 0);
        if (param1->unk_628 != 0) {
            func_02012444(param1->unk_628, g, 0);
        }
        param0[0x98] = 1;
    }
}
