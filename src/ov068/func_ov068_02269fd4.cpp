/* func_ov068_02269fd4 @ 0x02269fd4, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02269fd4 {
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
};

extern int data_021e5a2c;
extern "C" UnkStruct_02269fd4 *func_0201ce50(UnkStruct_02269fd4 *obj);
extern "C" int func_0207bb30(int *a, int b, int c);

extern "C" int func_ov068_02269fd4(int, UnkStruct_02269fd4 *obj, int limit)
{
    UnkStruct_02269fd4 *v6 = func_0201ce50(obj);
    int v4 = obj->v25();
    int v2 = v6->v25();
    if (func_0207bb30(&data_021e5a2c, v4, v2) >= 4) {
        if (limit < 0x6000) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
