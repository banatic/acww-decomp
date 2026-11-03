/* text_string: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051908 @ 0x02051908, 0x54 bytes, Thumb
 * func_02051880 @ 0x02051880, 0x86 bytes, Thumb
 * func_0205182c @ 0x0205182c, 0x52 bytes, Thumb
 */

class UnkStruct_02051908 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int GetLength();
    virtual unsigned short *GetBuffer();
};

extern "C" void MI_CpuCopy8(const void *src, void *dst, int size);
extern "C" void MI_CpuFill8(void *dst, int data, int size);
extern "C" int func_02050c58(unsigned short *out, const unsigned char *in);

class UnkStruct_02051880 {
  public:
    virtual void f0();
    virtual void f1();
    virtual unsigned int f8();
    virtual void *fC();
};

class UnkStruct_0205182c {
  public:
    virtual void vfn0();
    virtual void vfn1();
    virtual int vfn2();
    virtual unsigned short *vfn3();
};

extern "C" int func_02051908(UnkStruct_02051908 *self, const void *src, int srcLen)
{
    int count = srcLen;
    int len;
    unsigned short *buf;
    int diff;
    int success;

    len = self->GetLength();
    buf = self->GetBuffer();
    diff = len - count;
    success = diff >= 0 ? 1 : 0;
    if (!success) {
        count = len;
    }
    MI_CpuCopy8(src, buf, count * 2);
    if (diff > 0) {
        MI_CpuFill8(buf + count, 0, diff * 2);
    }
    return success;
}

extern "C" int func_02051880(UnkStruct_02051880 *a, UnkStruct_02051880 *b)
{
    unsigned char *inPtr = (unsigned char *) b->fC();
    unsigned int inputLen = b->f8();
    unsigned int total = 0;
    unsigned short *outPtr = (unsigned short *) a->fC();
    unsigned int outputLen = a->f8();
    unsigned int outIndex = 0;
    int result = 1;
    unsigned short ch;

    while (total < inputLen && outIndex < outputLen) {
        int adv = func_02050c58(&ch, inPtr);
        *outPtr = ch;
        outPtr++;
        outIndex++;
        inPtr += adv;
        total += adv;
    }

    if (outIndex >= outputLen && *inPtr != 0) {
        result = 0;
    }

    while (outIndex < outputLen) {
        *outPtr = 0;
        outIndex++;
        outPtr++;
    }

    return result;
}

extern "C" int func_0205182c(UnkStruct_0205182c *self, unsigned short *dst, int count)
{
    unsigned short *src;
    int limit;
    int flag;
    int n;
    int i;

    src = self->vfn3();
    limit = self->vfn2();
    flag = (count >= limit);
    n = flag ? limit : count;

    for (i = 0; i < n; i++) {
        dst[i] = src[i];
    }

    for (; i < count; i++) {
        dst[i] = 0;
    }

    return flag;
}
