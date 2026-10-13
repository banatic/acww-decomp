/* func_ov136_0229d184 @ 0x0229d184, 0x12c bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

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
