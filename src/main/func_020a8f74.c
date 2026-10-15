/* func_020a8f74 @ 0x020a8f74, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a8f74;
struct VTable {
    void *unk_00;
    void *p1;
    void *p2;
    int (*func)(struct UnkStruct_020a8f74 *);
};
struct UnkStruct_020a8f74 {
    struct VTable *vtable;
};

extern int func_020a8f88(int value);

int func_020a8f74(struct UnkStruct_020a8f74 *obj)
{
    return func_020a8f88(obj->vtable->func(obj));
}
