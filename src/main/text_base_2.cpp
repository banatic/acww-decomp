/* text_base_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a89dc @ 0x020a89dc, 0x1a bytes, Thumb
 * func_020a89ac @ 0x020a89ac, 0x30 bytes, Thumb
 * func_020a895c @ 0x020a895c, 0x4e bytes, Thumb
 */

class UnkStruct_020a89dc {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

extern "C" int func_020a89f8(void *dst, int value);
extern "C" int strcmp(int, int);

class UnkStruct_020a89ac {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
};

extern "C" void func_020a8c1c(void *);
extern "C" void MI_CpuCopy8(unsigned int a, unsigned int b, unsigned int c);

class UnkStruct_020a895c {
  public:
    virtual unsigned int v0();
    virtual unsigned int v1();
    virtual unsigned int v2();
    virtual unsigned int v3();
    unsigned int unk_04;
};

extern "C" int func_020a89dc(void *dst, UnkStruct_020a89dc *obj)
{
    return func_020a89f8(dst, obj->v3());
}

extern "C" int func_020a89ac(UnkStruct_020a89ac *a, UnkStruct_020a89ac *b)
{
    int x = b->f3();
    int y = a->f3();
    if (strcmp(y, x) == 0) {
        return 1;
    } else {
        return 0;
    }
}

extern "C" bool func_020a895c(UnkStruct_020a895c *obj, unsigned int b, unsigned int c)
{
    func_020a8c1c(obj);
    unsigned int v2 = obj->v3();
    unsigned int v1 = obj->v2();
    unsigned int diff = c - b;
    bool cond = (diff + 1) <= v1;
    if (cond) {
        obj->unk_04 = diff;
    } else {
        obj->unk_04 = v1 - 1;
    }
    MI_CpuCopy8(b, v2, obj->unk_04);
    return cond;
}
