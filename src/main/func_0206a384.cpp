/* func_0206a384 @ 0x0206a384, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void *func_0206807c(void *);
extern "C" void func_020a9334(void *, int);
extern "C" void func_020a7994(void *, int);

class VBase {
  public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual int getValue() = 0;
};

struct UnkStruct_0206a384 {
    char pad_00[0x24];
    void *unk_24;
};

extern "C" void func_0206a384(UnkStruct_0206a384 *obj)
{
    func_020a9334(obj, ((VBase *) func_0206807c(obj->unk_24))->getValue());
    func_020a7994((char *) obj->unk_24 + 0x1a58, ((VBase *) func_0206807c(obj->unk_24))->getValue());
    *((int *) ((char *) obj->unk_24 + 0x1a60)) = 1;
}
