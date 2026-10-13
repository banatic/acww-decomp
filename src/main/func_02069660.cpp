/* func_02069660 @ 0x02069660, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02069660 {
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
    virtual int v13(int, int);
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
};

extern "C" {
extern int func_020a86e4(void *, void *, void *, void *);
extern int func_020808ec(void);
extern int func_0206bb9c(void *, int, void *);
extern int func_0206b964(void *, void *);
extern int data_020df138;
}

extern "C" int func_02069660(void *a0)
{
    unsigned char buf[4];
    UnkStruct_02069660 *obj;

    obj = *(UnkStruct_02069660 **) (*(char **) ((char *) a0 + 0x24) + 0x14a8);

    obj->v13(0xd, 2);

    func_020a86e4((char *) a0 + 0x38, &buf[0], &buf[2], &buf[3]);
    buf[0] = (unsigned char) (buf[0] - 1);

    {
        int flag;
        int callResult = obj->v26();
        flag = 0;
        if (callResult) {
            int x = func_020808ec();
            if (x != buf[0]) {
                flag = 1;
            }
        } else {
            func_0206bb9c(a0, 0x1021, &data_020df138);
        }
        buf[1] = (&buf[2])[flag];
    }

    return func_0206b964(a0, &buf[1]);
}
