/* func_0201d2c8 @ 0x0201d2c8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0201d2c8 {
  public:
    virtual int vfunc_00();

  private:
    char pad[0x180];

  public:
    int (UnkStruct_0201d2c8::*pmf)();
};

extern "C" int func_0201d2c8(UnkStruct_0201d2c8 *obj)
{
    if (obj->pmf != 0) {
        return (obj->*obj->pmf)();
    }
    return 0;
}
