/* func_0201ccd0 @ 0x0201ccd0, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201ccd0 {
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
    virtual int target() = 0;
};

extern "C" unsigned int func_0208150c(unsigned int);
extern "C" int func_020036e8(unsigned char *);
extern "C" void func_0201b38c(void *, unsigned int);
extern "C" void func_0201b388(void *, unsigned int);
extern unsigned int data_020c8ed4[];
extern unsigned int data_020c8ee8[];

extern "C" void func_0201ccd0(int unused, UnkStruct_0201ccd0 *obj, int mode)
{
    int result = obj->target();
    if (mode == 4 && result != 0) {
        int r = func_020036e8((unsigned char *) func_0208150c(result));
        if (r == 0 || r == 3) {
            mode = 3;
        } else {
            mode = 2;
        }
    }
    func_0201b38c((char *) obj + 0x2a0, data_020c8ed4[mode]);
    func_0201b388((char *) obj + 0x2a0, data_020c8ee8[mode]);
}
