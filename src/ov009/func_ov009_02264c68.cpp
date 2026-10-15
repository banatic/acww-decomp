/* func_ov009_02264c68 @ 0x02264c68, 0x26 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02264c68 {
  public:
    virtual int v00();
    virtual int v01();
    virtual int v02();
    virtual int v03();
    virtual int v04();
    virtual int v05();
    virtual int v06();
    virtual int v07();
    virtual int v08();
    virtual int v09();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int v25();
    virtual int v26();
    virtual int v27();
    virtual int v28();
    virtual int v29();
    virtual int v30();
    virtual int v31();
    virtual int v32();
    virtual int v33();
    virtual int v34();
    virtual int target();
};

extern "C" int func_ov009_02264c40(void);
extern "C" int func_ov009_02264c68(UnkStruct_02264c68 *self)
{
    if (func_ov009_02264c40() && self->target()) {
        return 1;
    }
    return 0;
}
