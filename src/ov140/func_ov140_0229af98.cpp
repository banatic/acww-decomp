/* func_ov140_0229af98 @ 0x0229af98, 0xa0 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
void func_ov140_0229ac34(void *self);
void func_ov140_0229ac18(void *self);
}

class UnkStruct_0229af98 {
  public:
    unsigned char pad_00[0x8c];
    unsigned char idx;
};

typedef void (UnkStruct_0229af98::*PMF)();

extern PMF data_ov140_0229b370;
extern PMF data_ov140_0229b328;
extern PMF data_ov140_0229b360;
extern PMF data_ov140_0229b358;
extern PMF data_ov140_0229b350;

extern "C" int func_ov140_0229af98(UnkStruct_0229af98 *self)
{
    static PMF tbl[5] = {data_ov140_0229b370, data_ov140_0229b328, data_ov140_0229b360, data_ov140_0229b358,
                         data_ov140_0229b350};
    func_ov140_0229ac34(self);
    (self->*tbl[self->idx])();
    func_ov140_0229ac18(self);
    return 1;
}
