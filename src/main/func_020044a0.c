/* func_020044a0 @ 0x020044a0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct VTable VTable;
struct VTable {
    unsigned char pad_00[0x10];
    int (*func)(void *self);
};

typedef struct UnkStruct_020044a0 UnkStruct_020044a0;
struct UnkStruct_020044a0 {
    VTable *vtbl;
};

int func_020044a0(UnkStruct_020044a0 *self)
{
    return self->vtbl->func(self);
}
