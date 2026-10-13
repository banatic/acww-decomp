/* func_020b29c0 @ 0x020b29c0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern unsigned char data_020e54a8;
extern void *func_ov003_02220294(int);
extern int func_ov009_02264c90(void *);
}

class UnkStruct_020b29c0 {
  public:
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
    virtual void *v25();
};

extern "C" int func_020b29c0(int arg)
{
    int cond;
    UnkStruct_020b29c0 *obj;
    void *res;

    cond = (data_020e54a8 == 0) ? 1 : 0;
    if (cond == 0) {
        return 1;
    }
    obj = (UnkStruct_020b29c0 *) func_ov003_02220294(arg);
    if (obj != 0) {
        if (func_ov009_02264c90(obj) == 1) {
            res = obj->v25();
            if (res != 0) {
                return *(unsigned short *) ((char *) res + 4);
            }
            return 1;
        }
        return 1;
    }
    return 1;
}
