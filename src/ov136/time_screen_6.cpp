/* time_screen_6: 2 functions, module ov136
 * mwccarm 1.2/base -O4,s
 * func_ov136_0229d2b0 @ 0x0229d2b0, 0x94 bytes, Thumb
 * func_ov136_0229d184 @ 0x0229d184, 0x12c bytes, Thumb
 */

class Class {
  public:
    virtual void vfunc_00();
    char pad_04[0x88];
    unsigned char selector;
};

typedef void (Class::*PMF)();

extern PMF data_ov136_0229d468;
extern PMF data_ov136_0229d460;
extern PMF data_ov136_0229d470;
extern PMF data_ov136_0229d500;
extern "C" void func_ov136_0229cfb0(Class *);
extern "C" void func_ov136_0229cfa0(Class *);

class UnkStruct_0229d184 {
  public:
    char pad_00[0x8d];
    unsigned char m_index;
};

extern int data_ov136_0229d584;
extern void (UnkStruct_0229d184::*data_ov136_0229d5a8[16])();
extern void (UnkStruct_0229d184::*data_ov136_0229d4e8)();
extern void (UnkStruct_0229d184::*data_ov136_0229d4e0)();
extern void (UnkStruct_0229d184::*data_ov136_0229d4d8)();
extern void (UnkStruct_0229d184::*data_ov136_0229d4d0)();
extern void (UnkStruct_0229d184::*data_ov136_0229d4c8)();
extern void (UnkStruct_0229d184::*data_ov136_0229d4a0)();
extern void (UnkStruct_0229d184::*data_ov136_0229d4b0)();
extern void (UnkStruct_0229d184::*data_ov136_0229d4b8)();
extern void (UnkStruct_0229d184::*data_ov136_0229d4c0)();
extern void (UnkStruct_0229d184::*data_ov136_0229d4f8)();
extern void (UnkStruct_0229d184::*data_ov136_0229d498)();
extern void (UnkStruct_0229d184::*data_ov136_0229d490)();
extern void (UnkStruct_0229d184::*data_ov136_0229d488)();
extern void (UnkStruct_0229d184::*data_ov136_0229d480)();
extern void (UnkStruct_0229d184::*data_ov136_0229d478)();
extern void (UnkStruct_0229d184::*data_ov136_0229d4a8)();

extern "C" int func_ov136_0229d2b0(Class *obj)
{
    static int initialized = 0;
    static PMF table[4];
    if (!(initialized & 1)) {
        table[0] = data_ov136_0229d468;
        table[1] = data_ov136_0229d460;
        table[2] = data_ov136_0229d470;
        table[3] = data_ov136_0229d500;
        initialized |= 1;
    }
    func_ov136_0229cfb0(obj);
    (obj->*table[obj->selector])();
    func_ov136_0229cfa0(obj);
    return 1;
}

extern "C" void func_ov136_0229d184(UnkStruct_0229d184 *obj)
{
    if (!(data_ov136_0229d584 & 1)) {
        data_ov136_0229d5a8[0] = data_ov136_0229d4e8;
        data_ov136_0229d5a8[1] = data_ov136_0229d4e0;
        data_ov136_0229d5a8[2] = data_ov136_0229d4d8;
        data_ov136_0229d5a8[3] = data_ov136_0229d4d0;
        data_ov136_0229d5a8[4] = data_ov136_0229d4c8;
        data_ov136_0229d5a8[5] = data_ov136_0229d4a0;
        data_ov136_0229d5a8[6] = data_ov136_0229d4b0;
        data_ov136_0229d5a8[7] = data_ov136_0229d4b8;
        data_ov136_0229d5a8[8] = data_ov136_0229d4c0;
        data_ov136_0229d5a8[9] = data_ov136_0229d4f8;
        data_ov136_0229d5a8[10] = data_ov136_0229d498;
        data_ov136_0229d5a8[11] = data_ov136_0229d490;
        data_ov136_0229d5a8[12] = data_ov136_0229d488;
        data_ov136_0229d5a8[13] = data_ov136_0229d480;
        data_ov136_0229d5a8[14] = data_ov136_0229d478;
        data_ov136_0229d5a8[15] = data_ov136_0229d4a8;
        data_ov136_0229d584 |= 1;
    }
    (obj->*data_ov136_0229d5a8[obj->m_index])();
}
