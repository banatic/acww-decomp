/* func_020aac8c @ 0x020aac8c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020aac8c_2;
struct Result;

class UnkStruct_020aac8c {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

struct UnkStruct_020aac8c_2 {
    char pad_00[0x14];
    void *arr[5];
    char pad1[0x0c];
    int unk_34;
};

struct Result {
    char pad_00[0x10];
    int unk_10;
    char pad1[0x18];
    int unk_2C;
    char pad_30[0x08];
    char unk_38;
    char unk_39;
    char pad_3A[0x16];
    int unk_50;
    char pad_54[0x04];
    int unk_58;
};

extern "C" void *func_020ab550(int, unsigned int);
extern "C" int func_020ac318(unsigned int, int);
extern "C" UnkStruct_020aac8c *func_020ab798(void *);
extern "C" Result *func_020a9034(int, int, int);
extern "C" void func_0205166c(Result *, int);

extern "C" void func_020aac8c(UnkStruct_020aac8c_2 *p)
{
    unsigned int i;
    int x;
    UnkStruct_020aac8c *b;
    int z = 0;
    Result *r;
    void *tmp;

    for (i = 0; i < 5; i++) {
        tmp = func_020ab550(p->unk_34, i);
        x = func_020ac318(i, 5);
        b = func_020ab798(tmp);
        r = func_020a9034(x, 0xd, 2);
        if (r != 0) {
            r->unk_2C = 1;
            r->unk_10 = b->v3();
            r->unk_50 = 2;
            r->unk_39 = 0xe;
            r->unk_38 = (char) (i + 1);
            r->unk_58 = 2;
            func_0205166c(r, z);
            r->unk_58 = 0;
            p->arr[i] = r;
        }
    }
}
