/* func_020eebb4 @ 0x020eebb4, 0x94 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

class UnkStruct_020eebb4 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void call(int x);
    short unk_04;
    short count;
    int *arr;
};

extern "C" void func_020eebb4(UnkStruct_020eebb4 *self)
{
    if (self->arr == 0) {
        return;
    }
    if (self->unk_04 == 0) {
        return;
    }
    short *p = &self->count;
    self->count--;
    if (self->count < 0) {
        return;
    }
    do {
        self->call(self->arr[self->count]);
        (*p)--;
    } while (self->count >= 0);
}
