/* func_020039d4 @ 0x020039d4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef void (*Func)(void *);

struct UnkStruct_020039d4 {
    Func *vtable;
};

void func_020039d4(struct UnkStruct_020039d4 *obj)
{
    obj->vtable[3](obj);
}
