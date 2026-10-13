/* func_ov045_02260c94 @ 0x02260c94, 0x1a bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02260c94 {
  public:
    virtual void v0(void);
    virtual void v1(void);
    virtual void v2(void);
    char pad_04[0xb0];
    void *unk_B4;
};

extern "C" void func_ov045_02260c94(UnkStruct_02260c94 *obj, void *arg)
{
    obj->v2();
    obj->unk_B4 = arg;
}
