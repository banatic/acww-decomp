/* func_02034e28 @ 0x02034e28, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_02034e28_2 {
  public:
    virtual ~UnkStruct_02034e28_2() {}

  private:
    char pad[24];
};

struct UnkStruct_02034e28 {
    UnkStruct_02034e28_2 arr[16];
    int count;
};

void func_02034e28(UnkStruct_02034e28 *self, void (UnkStruct_02034e28_2::*pmf)())
{
    int i;
    for (i = 0; i < self->count; i++) {
        (self->arr[i].*pmf)();
    }
}
}
