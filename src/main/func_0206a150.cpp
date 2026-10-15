/* func_0206a150 @ 0x0206a150, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020679b0(void *);
extern "C" void func_0206bb9c(void *object, int code, const void *message);
extern "C" int func_020a82f8(void *);
extern "C" void func_020a9334(void *, int);
extern "C" void func_020a7994(void *, int);

class CMain {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int action();
};

typedef struct {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[0x34];
    void *unk_5C;
} ParamType;

extern unsigned char data_020df1a8[];

extern "C" void func_0206a150(ParamType *p)
{
    if (func_020679b0(p->unk_24) == 0) {
        func_0206bb9c(p, 0x0ccb, &data_020df1a8);
    }

    int idx1 = func_020a82f8(p->unk_5C);
    func_020a9334(p, idx1);

    int ret1 = ((CMain *) ((char *) p->unk_24 + 0x1ccc))->action();
    func_020a9334(p, ret1);

    int idx2 = func_020a82f8((void *) 6);
    func_020a9334(p, idx2);

    int ret2 = ((CMain *) ((char *) p->unk_24 + 0x1ccc))->action();
    func_020a7994((char *) p->unk_24 + 0x1a58, ret2);

    *((unsigned int *) ((char *) p->unk_24 + 0x1a60)) = 0;
}
