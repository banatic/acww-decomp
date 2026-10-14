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
extern PMF data_020e38a8, data_020e3918, data_020e3930, data_020e3968, data_020e39d8, data_020e3a60, __ptmf_null;

extern "C" int func_020a2120(UnkStruct_020a2120 *self, void *arg)
{
    static unsigned int guard = 0;
    static PMF table[7];

    if ((guard & 1) == 0) {
        table[0] = data_020e38a8;
        table[1] = data_020e3918;
        table[2] = data_020e3930;
        table[3] = data_020e3968;
        table[4] = data_020e39d8;
        table[5] = data_020e3a60;
        table[6] = __ptmf_null;
        guard |= 1;
    }

    int result = 3;
    if (table[self->idx] != 0) {
        result = (self->*table[self->idx])(arg);
    }
    if (self->idx == 6) {
        self->idx = 0;
        return 0;
    }
    return result;
}