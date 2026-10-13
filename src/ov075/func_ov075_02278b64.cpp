/* func_ov075_02278b64 @ 0x02278b64, 0x1a bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

struct FuncOv075Class {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    char pad_04[0xb4];
    int unk_B8;
};

extern "C" void func_ov075_02278b64(FuncOv075Class *obj, int value)
{
    obj->m2();
    obj->unk_B8 = value;
}
