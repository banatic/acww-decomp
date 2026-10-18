/* func_02014158 @ 0x02014158, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02014158 {
  public:
    virtual void method(void *arg);
};
typedef void (UnkStruct_02014158::*PMF)(void *);
struct UnkStruct_02014158_2 {
    char pad_00[10];
    unsigned char a;
};
extern PMF data_020d8804;
extern PMF data_020d884c;
extern int data_021c14f4;
extern PMF data_021c163c[2];

extern "C" void func_02014158(UnkStruct_02014158_2 *obj, void *arg1)
{
    if (!(data_021c14f4 & 1)) {
        data_021c163c[0] = data_020d8804;
        data_021c163c[1] = data_020d884c;
        data_021c14f4 |= 1;
    }
    unsigned char idx = obj->a;
    if (idx < 2) {
        (reinterpret_cast<UnkStruct_02014158 *>(obj)->*data_021c163c[idx])(arg1);
    }
}
