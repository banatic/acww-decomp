/* func_02062da4 @ 0x02062da4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02062da4 {
  public:
    virtual void f0();
    virtual void f1();
    virtual int GetSize();
    char pad_04[10];
    char data[1];
};

extern "C" void MI_CpuCopy8(void *dest, const void *src, int len);

extern "C" int func_02062da4(UnkStruct_02062da4 *obj, void *src, int c)
{
    if (c >= obj->GetSize()) {
        int n = obj->GetSize();
        MI_CpuCopy8(&obj->data, src, n * 2);
        return 1;
    }
    return 0;
}
