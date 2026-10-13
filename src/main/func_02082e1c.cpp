/* func_02082e1c @ 0x02082e1c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_02083544(int, signed char);

class UnkStruct_02082e1c {
  public:
    virtual int m1();
    virtual int m2();
    virtual int m3();
    signed char unk_04;
};

extern "C" int func_02082e1c(UnkStruct_02082e1c *obj)
{
    int x = obj->m3();
    int y = 0;
    if (x != 0) {
        y = func_02083544(x, obj->unk_04);
    }
    return y;
}
