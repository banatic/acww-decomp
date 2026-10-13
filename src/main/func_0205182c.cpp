/* func_0205182c @ 0x0205182c, 0x52 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0205182c {
  public:
    virtual void vfn0();
    virtual void vfn1();
    virtual int vfn2();
    virtual unsigned short *vfn3();
};

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
