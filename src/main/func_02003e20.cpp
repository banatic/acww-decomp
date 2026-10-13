/* func_02003e20 @ 0x02003e20, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_02003e20;

class Object {
  public:
    virtual void vfunc0();
    virtual void vfunc1();
    virtual void method(void *param, UnkStruct_02003e20 *v);
};

extern "C" int data_021c67a4;
extern "C" UnkStruct_02003e20 data_021c67b8;

extern "C" void func_02003e20(Object *self, void *param, UnkStruct_02003e20 *v)
{
    if (v != 0) {
        UnkStruct_02003e20 t = *v;
        if (data_021c67a4 == 0) {
            return;
        }
        t.x = t.x - data_021c67b8.x;
        t.y = t.y - data_021c67b8.y;
        t.z = t.z - data_021c67b8.z;
        self->method(param, &t);
    } else {
        self->method(param, 0);
    }
}
