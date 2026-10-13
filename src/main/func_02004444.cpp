/* func_02004444 @ 0x02004444, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02004444 {
    int x;
    int y;
    int z;
};

extern UnkStruct_02004444 data_021c67b8;
extern void *data_021c67a4;

class UnkStruct_02004444_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3(UnkStruct_02004444 *p);
};

extern "C" void func_02004444(UnkStruct_02004444_2 *self, UnkStruct_02004444 *arg)
{
    if (arg) {
        if (data_021c67a4) {
            UnkStruct_02004444 d;
            d.x = arg->x - data_021c67b8.x;
            d.y = arg->y - data_021c67b8.y;
            d.z = arg->z - data_021c67b8.z;
            self->f3(&d);
        }
    } else {
        self->f3(arg);
    }
}
