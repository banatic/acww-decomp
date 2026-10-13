/* func_020ab1a0 @ 0x020ab1a0, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Obj1;
struct Obj2;
class UnkStruct_020ab1a0;

extern "C" {
int func_020ab51c(void *p);
Obj1 *func_020ab550(void *p, unsigned int i);
int func_020ac318(unsigned int a, unsigned int b);
UnkStruct_020ab1a0 *func_020ab798(Obj1 *o);
Obj2 *func_020a9034(int a, int b, int c);
void func_0205166c(Obj2 *o, int v);
}

struct Obj2 {
    char pad_00[0x10];
    int unk_10;
    char pad1[0x18];
    int unk_2C;
    char pad_30[0x8];
    char unk_38;
    char unk_39;
    char pad_3A[0x16];
    int unk_50;
    char pad_54[0x3];
    char unk_57;
    int unk_58;
};

class UnkStruct_020ab1a0 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual int vf3();
};

struct UnkStruct_020ab1a0_2 {
    char pad_00[8];
    Obj2 *arr[1];
    char pad1[0x14];
    void *unk_20;
};

extern "C" void func_020ab1a0(UnkStruct_020ab1a0_2 *ctx)
{
    unsigned int i;
    unsigned int count;
    Obj1 *obj1;
    Obj2 *obj2;
    int local0;
    UnkStruct_020ab1a0 *local4;
    int local8 = 0;
    int localC = 0;

    count = func_020ab51c(ctx->unk_20);
    for (i = 0; i < count; i++) {
        obj1 = func_020ab550(ctx->unk_20, i);
        local0 = func_020ac318(i, count);
        local4 = func_020ab798(obj1);
        obj2 = func_020a9034(local0, 0xd, 2);
        if (obj2 != 0) {
            obj2->unk_2C = 1;
            obj2->unk_10 = local4->vf3();
            obj2->unk_50 = 2;
            obj2->unk_39 = 0xe;
            obj2->unk_38 = (char) (i + 1);
            obj2->unk_57 = 1;
            obj2->unk_58 = 2;
            func_0205166c(obj2, local8);
            obj2->unk_58 = localC;
            ctx->arr[i] = obj2;
        }
    }
}
