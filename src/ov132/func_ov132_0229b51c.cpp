/* func_ov132_0229b51c @ 0x0229b51c, 0x18 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov132_0229b4fc(void *);

struct UnkStruct_0229b51c {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

struct UnkStruct_0229b51c_2 {
    char pad_00[0x94];
    UnkStruct_0229b51c member;
};

extern "C" void func_ov132_0229b51c(UnkStruct_0229b51c_2 *obj)
{
    func_ov132_0229b4fc(obj);
    obj->member.vf3();
}
