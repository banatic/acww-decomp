/* func_ov076_02278e04 @ 0x02278e04, 0x30 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02278e04 {
    unsigned char pad[0x71c];
    unsigned char byte;
};

struct UnkStruct_02278e04_2 {
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void method();
    unsigned char pad[0xac];
    int unk_B0;
    UnkStruct_02278e04 *unk_B4;
};

extern "C" void func_ov076_02278e04(UnkStruct_02278e04_2 *a, UnkStruct_02278e04 *b)
{
    a->method();
    a->unk_B4 = b;
    UnkStruct_02278e04 *p = a->unk_B4;
    p->byte = 0;
    a->unk_B0 = 0;
}
