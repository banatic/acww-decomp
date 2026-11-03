/* talk_tags_20: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206a264 @ 0x0206a264, 0x48 bytes, Thumb
 * func_0206a21c @ 0x0206a21c, 0x48 bytes, Thumb
 * func_0206a1d4 @ 0x0206a1d4, 0x48 bytes, Thumb
 * func_0206a150 @ 0x0206a150, 0x84 bytes, Thumb
 */

struct UnkStruct_0206a264 {
    unsigned char pad_00[0x1a58];
    int x;
    int pad_1A5C;
    int z;
};

struct UnkStruct_0206a264_2 {
    unsigned char pad_00[0x24];
    UnkStruct_0206a264 *unk_24;
};

class UnkStruct_0206a264_3 {
  public:
    virtual int f1() = 0;
    virtual int f2() = 0;
    virtual int f3() = 0;
    virtual int f4() = 0;
};

extern "C" UnkStruct_0206a264_3 *func_02067fd4(UnkStruct_0206a264 *);
extern "C" void func_020a9334(UnkStruct_0206a264_2 *, int);

class UnkStruct_0206a21c_2 {
  public:
    virtual int method0();
    virtual int method1();
    virtual int method2();
    virtual int method3();
};

struct UnkStruct_0206a21c {
    char pad_00[0x24];
    void *unk_24;
};

extern "C" UnkStruct_0206a21c_2 *func_02067fa4(void *);
extern "C" void func_020a7994(void *, int);

typedef struct UnkStruct_0206a1d4 UnkStruct_0206a1d4;

typedef struct UnkStruct_0206a1d4_2 {
    char pad_00[0x24];
    UnkStruct_0206a1d4 *unk_24;
} UnkStruct_0206a1d4_2;

class UnkStruct_0206a1d4_3 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int vfunc();
};

extern "C" UnkStruct_0206a1d4_3 *func_02067f74(UnkStruct_0206a1d4 *p);
extern "C" int func_020679b0(void *);
extern "C" void func_0206bb9c(void *object, int code, const void *message);
extern "C" int func_020a82f8(void *);

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

extern "C" void func_0206a264(UnkStruct_0206a264_2 *p)
{
    int r;
    r = func_02067fd4(p->unk_24)->f4();
    func_020a9334(p, r);
    r = func_02067fd4(p->unk_24)->f4();
    func_020a7994((void *) (&p->unk_24->x), r);
    p->unk_24->z = 1;
}

extern "C" void func_0206a21c(UnkStruct_0206a21c *param)
{
    func_020a9334((UnkStruct_0206a264_2 *) param, func_02067fa4(param->unk_24)->method3());
    func_020a7994((char *) param->unk_24 + 0x1a58, func_02067fa4(param->unk_24)->method3());
    *((unsigned int *) ((char *) param->unk_24 + 0x1a60)) = 1;
}

extern "C" void func_0206a1d4(UnkStruct_0206a1d4_2 *self)
{
    func_020a9334((UnkStruct_0206a264_2 *) self, func_02067f74(self->unk_24)->vfunc());
    func_020a7994((void *) ((char *) self->unk_24 + 0x1a58), func_02067f74(self->unk_24)->vfunc());
    *(int *) ((char *) self->unk_24 + 0x1a60) = 1;
}

extern "C" void func_0206a150(ParamType *p)
{
    if (func_020679b0(p->unk_24) == 0) {
        func_0206bb9c(p, 0x0ccb, &data_020df1a8);
    }

    int idx1 = func_020a82f8(p->unk_5C);
    func_020a9334((UnkStruct_0206a264_2 *) p, idx1);

    int ret1 = ((CMain *) ((char *) p->unk_24 + 0x1ccc))->action();
    func_020a9334((UnkStruct_0206a264_2 *) p, ret1);

    int idx2 = func_020a82f8((void *) 6);
    func_020a9334((UnkStruct_0206a264_2 *) p, idx2);

    int ret2 = ((CMain *) ((char *) p->unk_24 + 0x1ccc))->action();
    func_020a7994((char *) p->unk_24 + 0x1a58, ret2);

    *((unsigned int *) ((char *) p->unk_24 + 0x1a60)) = 0;
}
