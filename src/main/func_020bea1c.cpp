/* func_020bea1c @ 0x020bea1c, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020bea1c {
  public:
    int idx;
};

extern "C" void func_020bea1c(UnkStruct_020bea1c *self)
{
    extern void (UnkStruct_020bea1c::*data_0213dd98)();
    extern void (UnkStruct_020bea1c::*data_020e5af8)();
    extern void (UnkStruct_020bea1c::*data_020e5ac0)();
    extern void (UnkStruct_020bea1c::*data_020e5a00)();
    extern void (UnkStruct_020bea1c::*data_020e5bd0)();
    extern void (UnkStruct_020bea1c::*data_020e5ce8)();
    extern void (UnkStruct_020bea1c::*data_020e5a68)();
    extern void (UnkStruct_020bea1c::*data_020e59a0)();
    extern void (UnkStruct_020bea1c::*data_020e5988)();
    extern void (UnkStruct_020bea1c::*data_020e5be0)();

    static void (UnkStruct_020bea1c::*tbl[10])() = {data_0213dd98, data_020e5af8, data_020e5ac0, data_020e5a00, data_020e5bd0,
                                                    data_020e5ce8, data_020e5a68, data_020e59a0, data_020e5988, data_020e5be0};

    void (UnkStruct_020bea1c::*pmf)() = tbl[self->idx];
    if (pmf) {
        (self->*pmf)();
    }
}
