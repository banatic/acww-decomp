/* func_020c3350 @ 0x020c3350, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020c3350 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    char pad_04[0xb0 - 4];
    void *unk_B0;
};

extern "C" void func_020c3350(UnkStruct_020c3350 *self, void *value)
{
    self->v2();
    self->unk_B0 = value;
}
