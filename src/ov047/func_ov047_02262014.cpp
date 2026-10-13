/* func_ov047_02262014 @ 0x02262014, 0x80 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02262014 {
  public:
    virtual void vf0();
    char pad_04[0xb4];
    void (UnkStruct_02262014::*cb)();
    void (UnkStruct_02262014::*pending)();
};

typedef void (UnkStruct_02262014::*PMF)();

extern PMF data_0213dd98;

extern "C" void func_ov047_02262014(UnkStruct_02262014 *self)
{
    if (self->cb) {
        (self->*self->cb)();
        PMF tmp = data_0213dd98;
        self->cb = tmp;
        if (self->pending) {
            self->cb = self->pending;
            self->pending = tmp;
        }
    }
}
