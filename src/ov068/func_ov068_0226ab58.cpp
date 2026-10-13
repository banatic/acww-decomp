/* func_ov068_0226ab58 @ 0x0226ab58, 0xe8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226ab58_2 {
  public:
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
    virtual int v25();
};

typedef struct UnkStruct_0226ab58 {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
} UnkStruct_0226ab58;

extern "C" {
extern UnkStruct_0226ab58_2 *func_0201ce50(UnkStruct_0226ab58_2 *obj);
extern void func_ov068_0226aca8(UnkStruct_0226ab58 *self, int *out0, int *out1, int v, int w);
extern void func_0207daf4(int a, int b);
extern void func_020801c4(int a, int b, int c);
extern void func_ov068_0226ada8(UnkStruct_0226ab58 *self, UnkStruct_0226ab58_2 *obj, char *data);
extern int func_0207bb30(char *data, int a, int b);
extern void func_ov068_0226ad78(UnkStruct_0226ab58 *self, UnkStruct_0226ab58_2 *obj, int a3, int a4, int a5);
extern void func_ov068_0226ad44(UnkStruct_0226ab58 *self, UnkStruct_0226ab58_2 *obj, char *data, int a4, int a5, int a6);
extern char data_ov068_0227674c[];
extern char data_ov068_02276728[];
extern char data_021e5a2c[];

int func_ov068_0226ab58(UnkStruct_0226ab58 *self, UnkStruct_0226ab58_2 *obj)
{
    UnkStruct_0226ab58_2 *obj2;
    int a, b, c;
    int local0, local1;
    int d;
    int r;

    obj2 = func_0201ce50(obj);
    a = obj->v25();
    b = obj2->v25();
    local0 = 0;
    local1 = 0;
    c = obj->v25();
    d = obj2->v25();

    func_ov068_0226aca8(self, &local0, &local1, c, d);
    func_0207daf4(local1, local0);
    func_020801c4(local1, local0, 0);
    func_ov068_0226ada8(self, obj, data_ov068_0227674c);
    r = func_0207bb30(data_021e5a2c, a, b);

    switch (r) {
        case 0:
        case 1:
            func_ov068_0226ad78(self, obj, 1, 2, 1);
            func_ov068_0226ad78(self, obj2, 1, 2, 1);
            break;
        case 2:
            break;
        case 3:
        case 4:
            func_ov068_0226ad44(self, obj, data_ov068_02276728, 2, 2, 1);
            func_ov068_0226ad44(self, obj2, data_ov068_02276728, 2, 2, 1);
            break;
    }

    self->unk_1C = 3;
    return 1;
}
}
