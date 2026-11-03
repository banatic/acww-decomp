/* label_box_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a8fb8 @ 0x020a8fb8, 0x30 bytes, Thumb
 * func_020a8f88 @ 0x020a8f88, 0x2e bytes, Thumb
 */

class UnkStruct_020a8fb8 {
  public:
    virtual void virtual0();
};

extern "C" void NNS_FndRemoveListObject(void *a, UnkStruct_020a8fb8 *b);
extern "C" void func_020e993c(int a, UnkStruct_020a8fb8 *b);
extern int data_021c81bc;
extern int data_021c8194;

class UnkStruct_020a8f88 {
  public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    char pad_04[12];
    int unk_10;
};

extern "C" UnkStruct_020a8f88 *func_020a9034(int a, int b, int c);

extern "C" void func_020a8fb8(UnkStruct_020a8fb8 *p)
{
    if (p) {
        NNS_FndRemoveListObject(&data_021c81bc, p);
        p->virtual0();
        func_020e993c(data_021c8194, p);
    }
}

extern "C" int func_020a8f88(int arg0)
{
    int result = 0;
    UnkStruct_020a8f88 *obj = func_020a9034(0, 1, 2);
    if (obj) {
        obj->unk_10 = arg0;
        result = obj->v3();
    }
    func_020a8fb8((UnkStruct_020a8fb8 *) obj);
    return result;
}
