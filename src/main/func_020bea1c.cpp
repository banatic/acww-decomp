/* func_020bea1c @ 0x020bea1c, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020bea1c {
  public:
    int idx;
};

extern int data_021f6cc4;
extern void (UnkStruct_020bea1c::*data_021f6d48[10])();

extern "C" void func_020bea1c(UnkStruct_020bea1c *self)
{
    extern void (UnkStruct_020bea1c::*__ptmf_null)();
    extern void (UnkStruct_020bea1c::*data_020e5af8)();
    extern void (UnkStruct_020bea1c::*data_020e5ac0)();
    extern void (UnkStruct_020bea1c::*data_020e5a00)();
    extern void (UnkStruct_020bea1c::*data_020e5bd0)();
    extern void (UnkStruct_020bea1c::*data_020e5ce8)();
    extern void (UnkStruct_020bea1c::*data_020e5a68)();
    extern void (UnkStruct_020bea1c::*data_020e59a0)();
    extern void (UnkStruct_020bea1c::*data_020e5988)();
    extern void (UnkStruct_020bea1c::*data_020e5be0)();

    if (!(data_021f6cc4 & 1)) {
        data_021f6d48[0] = __ptmf_null;
        data_021f6d48[1] = data_020e5af8;
        data_021f6d48[2] = data_020e5ac0;
        data_021f6d48[3] = data_020e5a00;
        data_021f6d48[4] = data_020e5bd0;
        data_021f6d48[5] = data_020e5ce8;
        data_021f6d48[6] = data_020e5a68;
        data_021f6d48[7] = data_020e59a0;
        data_021f6d48[8] = data_020e5988;
        data_021f6d48[9] = data_020e5be0;
        data_021f6cc4 |= 1;
    }

    void (UnkStruct_020bea1c::*pmf)() = data_021f6d48[self->idx];
    if (pmf) {
        (self->*pmf)();
    }
}
