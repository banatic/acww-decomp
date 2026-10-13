/* func_020c3c20 @ 0x020c3c20, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020c3c20 {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    char pad_04[0xac];
    int unk_B0;
    int unk_B4;
};

extern "C" void func_020c3c20(UnkStruct_020c3c20 *obj, int val)
{
    obj->f2();
    obj->unk_B4 = val;
    obj->unk_B0 = 1;
}
