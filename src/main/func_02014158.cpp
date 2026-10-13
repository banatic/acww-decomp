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
extern "C" void func_02014158(UnkStruct_02014158_2 *obj, void *arg1)
{
    static PMF table[2] = {data_020d8804, data_020d884c};
    unsigned char idx = obj->a;
    if (idx < 2) {
        (reinterpret_cast<UnkStruct_02014158 *>(obj)->*table[idx])(arg1);
    }
}
