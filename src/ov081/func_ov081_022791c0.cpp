/* func_ov081_022791c0 @ 0x022791c0, 0x80 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022791c0 {
  public:
    char pad_00[0xb4];
    void (UnkStruct_022791c0::*pmf0)();
    void (UnkStruct_022791c0::*pmf1)();
};

extern void (UnkStruct_022791c0::*data_0213dd98)();

extern "C" void func_ov081_022791c0(UnkStruct_022791c0 *self)
{
    if (self->pmf0) {
        (self->*self->pmf0)();
        void (UnkStruct_022791c0::*g)() = data_0213dd98;
        self->pmf0 = g;
        if (self->pmf1) {
            self->pmf0 = self->pmf1;
            self->pmf1 = g;
        }
    }
}
