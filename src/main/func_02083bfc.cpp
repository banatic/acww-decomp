/* func_02083bfc @ 0x02083bfc, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02083bfc {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual const unsigned char *getString(int i);
    int count;
};

extern "C" int func_02083bfc(UnkStruct_02083bfc *self)
{
    int i = 0;
    int result = -1;
    for (; i < self->count; i++) {
        const unsigned char *s = self->getString(i);
        if (s && *s == 0) {
            result = i;
            break;
        }
    }
    return result;
}
