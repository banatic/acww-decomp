/* func_ov144_0229b130 @ 0x0229b130, 0x94 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov144_0229ad90(void *obj);
extern "C" void func_ov144_0229ad70(void *obj);

class UnkStruct_0229b130 {
  public:
    char pad_00[0x8c];
    unsigned char idx;
};

typedef void (UnkStruct_0229b130::*PMF)();

extern PMF data_ov144_0229b3a0;
extern PMF data_ov144_0229b3a8;
extern PMF data_ov144_0229b350;
extern PMF data_ov144_0229b398;

extern "C" int func_ov144_0229b130(UnkStruct_0229b130 *obj)
{
    static int initialized = 0;
    static PMF table[4];

    if ((initialized & 1) == 0) {
        table[0] = data_ov144_0229b3a0;
        table[1] = data_ov144_0229b3a8;
        table[2] = data_ov144_0229b350;
        table[3] = data_ov144_0229b398;
        initialized |= 1;
    }

    func_ov144_0229ad90(obj);
    (obj->*table[obj->idx])();
    func_ov144_0229ad70(obj);
    return 1;
}
