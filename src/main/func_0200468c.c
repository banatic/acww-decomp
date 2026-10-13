/* func_0200468c @ 0x0200468c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0200468c;

typedef void (*funcptr)(struct UnkStruct_0200468c *);

struct VTable {
    char pad_00[0x14];
    funcptr func;
};

struct UnkStruct_0200468c {
    struct VTable *vtable;
};

extern struct UnkStruct_0200468c *data_0213fff0;

void func_0200468c(void)
{
    struct UnkStruct_0200468c *obj = data_0213fff0;
    obj->vtable->func(obj);
}
