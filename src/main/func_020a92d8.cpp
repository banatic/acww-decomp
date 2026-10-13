/* func_020a92d8 @ 0x020a92d8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a92d8;

extern "C" int func_020a9368(UnkStruct_020a92d8 *self, int value);

class UnkStruct_020a92d8 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual int vf6();
    int unk_04;
};

extern "C" int func_020a92d8(UnkStruct_020a92d8 *self, int value)
{
    int result = 0;
    do {
        if (self->unk_04 == value) {
            self->vf3();
            break;
        }
        if (self->vf6() == 0) {
            result = self->unk_04;
            break;
        }
    } while (func_020a9368(self, result) != 0);
    return result;
}
