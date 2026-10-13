/* func_020a9354 @ 0x020a9354, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct VTable;

struct UnkStruct_020a9354 {
    struct VTable *vtbl;
    int unk_04;
};

struct VTable {
    void (*func0)(struct UnkStruct_020a9354 *);
    void (*func1)(struct UnkStruct_020a9354 *);
    void (*func2)(struct UnkStruct_020a9354 *);
};

void func_020a9354(struct UnkStruct_020a9354 *obj, int val)
{
    obj->unk_04 = val;
    obj->vtbl->func2(obj);
}
