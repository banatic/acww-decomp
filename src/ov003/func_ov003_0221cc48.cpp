/* func_ov003_0221cc48 @ 0x0221cc48, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern "C" {

class UnkStruct_0221cc48 {
  public:
    char pad_00[0x134];
    unsigned char state;
    void f0();
    void f1();
};

typedef void (UnkStruct_0221cc48::*PMF)();

extern PMF data_ov003_02238ab8;
extern PMF data_ov003_02238ad0;

void func_ov003_0221cc48(UnkStruct_0221cc48 *obj)
{
    static int initialized;
    static PMF table[3];

    if (!(initialized & 1)) {
        table[0] = data_ov003_02238ab8;
        table[1] = data_ov003_02238ad0;
        initialized |= 1;
    }

    if (obj->state < 3) {
        (obj->*table[obj->state])();
    }
}
}
