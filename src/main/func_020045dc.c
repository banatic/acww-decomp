/* func_020045dc @ 0x020045dc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct VTable {
    int pad_00[8];
    void (*method20)(void *);
};
struct Object {
    struct VTable *vtable;
};
extern struct Object *data_0213fff0;

void func_020045dc(void)
{
    data_0213fff0->vtable->method20(data_0213fff0);
}
