/* func_02082e90 @ 0x02082e90, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_02083684(int, int);

class UnkStruct_02082e90 {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    signed char unk_04;
};

extern "C" int func_02082e90(UnkStruct_02082e90 *self)
{
    int v = self->f2();
    int r = 0;
    if (v != 0) {
        r = func_02083684(v, self->unk_04);
    }
    return r;
}
