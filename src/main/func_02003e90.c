/* func_02003e90 @ 0x02003e90, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02003e90;
struct Vtbl {
    void (*func)(struct UnkStruct_02003e90 *);
};
struct UnkStruct_02003e90 {
    struct Vtbl *vtbl;
};
void func_02003e90(struct UnkStruct_02003e90 *obj)
{
    obj->vtbl->func(obj);
}
