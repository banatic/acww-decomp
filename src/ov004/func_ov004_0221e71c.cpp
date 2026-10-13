/* func_ov004_0221e71c @ 0x0221e71c, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0221e71c {
  public:
    char pad_00[0xc];
    unsigned char k;
};
typedef void (UnkStruct_0221e71c::*PMF)(void *a);
extern PMF data_ov004_0225399c;

extern "C" int func_ov004_0221e71c(UnkStruct_0221e71c *self, void *a)
{
    static PMF tbl[1] = {data_ov004_0225399c};
    unsigned char k;

    k = self->k;
    if (k < 1) {
        (self->*tbl[k])(a);
    }
    return 0;
}
