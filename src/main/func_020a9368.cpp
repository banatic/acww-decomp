/* func_020a9368 @ 0x020a9368, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a9368 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4(int);
    char *unk_04;
    char unk_08[1];
};

extern "C" int func_020a9c9c(void *);
extern "C" void func_020a9318(UnkStruct_020a9368 *);
extern "C" void func_020a93f4(UnkStruct_020a9368 *);

extern "C" int func_020a9368(UnkStruct_020a9368 *self, int a1)
{
    char *p = self->unk_04;
    int ret = 1;
    int val = ((p[1] << 8) & 0xff00) | (p[0] & 0xff);
    if (val == 0 || (a1 != 0 && val == 10)) {
        if (func_020a9c9c(&self->unk_08[0])) {
            self->f3();
            ret = 0;
        } else {
            func_020a9318(self);
        }
    } else {
        if (val == 0x1a) {
            func_020a93f4(self);
        } else {
            self->unk_04 += 2;
            self->f4(val);
        }
    }
    return ret;
}
