/* func_020a895c @ 0x020a895c, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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
