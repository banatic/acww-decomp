/* func_ov074_0227910c @ 0x0227910c, 0x44 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0227910c {
  public:
    void method();
};

class UnkStruct_0227910c_2 : public UnkStruct_0227910c {
  public:
    char pad[0xB4 - sizeof(UnkStruct_0227910c)];
    void (UnkStruct_0227910c::*pmf)();
};

extern void (UnkStruct_0227910c::*data_0213dd98)();

extern "C" void func_ov074_0227910c(UnkStruct_0227910c_2 *obj)
{
    if (obj->pmf) {
        (obj->*obj->pmf)();
        obj->pmf = data_0213dd98;
    }
}
