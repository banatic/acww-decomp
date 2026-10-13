/* func_02004290 @ 0x02004290, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vtbl {
    char pad_00[12];
    void (*fn)(void *self, void *arg);
} Vtbl;

typedef struct UnkStruct_02004290 {
    Vtbl *vtbl;
} UnkStruct_02004290;

void func_02004290(void *self, void *arg)
{
    UnkStruct_02004290 *obj = (UnkStruct_02004290 *) self;
    obj->vtbl->fn(self, arg);
}
