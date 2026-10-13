/* func_02051908 @ 0x02051908, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
