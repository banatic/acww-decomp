/* func_02082fec @ 0x02082fec, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02082fec {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    signed char unk_04;
};

extern "C" int func_02083a80(int a, int b, int c);

extern "C" int func_02082fec(UnkStruct_02082fec *self, int arg)
{
    int r = self->f2();
    int result = 0;
    if (r) {
        result = func_02083a80(r, self->unk_04, arg);
    }
    return result;
}
