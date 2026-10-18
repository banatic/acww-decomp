/* func_020a2120 @ 0x020a2120, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a2120 {
  public:
    virtual void vfunc_00() {}
    unsigned char pad[0x9c];
    unsigned char idx;
};

typedef int (UnkStruct_020a2120::*PMF)(void *);
extern unsigned int data_021f3c2c;
extern PMF data_021f3c84[7];
extern PMF data_020e38a8, data_020e3918, data_020e3930, data_020e3968, data_020e39d8, data_020e3a60, __ptmf_null;

extern "C" int func_020a2120(UnkStruct_020a2120 *self, void *arg)
{
    if ((data_021f3c2c & 1) == 0) {
        data_021f3c84[0] = data_020e38a8;
        data_021f3c84[1] = data_020e3918;
        data_021f3c84[2] = data_020e3930;
        data_021f3c84[3] = data_020e3968;
        data_021f3c84[4] = data_020e39d8;
        data_021f3c84[5] = data_020e3a60;
        data_021f3c84[6] = __ptmf_null;
        data_021f3c2c |= 1;
    }

    int result = 3;
    if (data_021f3c84[self->idx] != 0) {
        result = (self->*data_021f3c84[self->idx])(arg);
    }
    if (self->idx == 6) {
        self->idx = 0;
        return 0;
    }
    return result;
}