/* func_020ac278 @ 0x020ac278, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_0208e594(void *obj, int a, int b);

class UnkStruct_020ac278_2 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

struct UnkStruct_020ac278 {
    char pad_00[0x1c];
    short unk_1C;
    char pad_1E[2];
    UnkStruct_020ac278_2 obj;
    char pad_24[0x48];
    int unk_6C;
};

extern "C" void func_020ac278(UnkStruct_020ac278 *s)
{
    func_0208e594(&s->obj, 5, s->unk_1C + ((s->unk_6C << 4) - 4));
    s->obj.vf3();
}
