/* func_0205967c @ 0x0205967c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0205967c UnkStruct_0205967c;
typedef struct VTable VTable;
struct VTable {
    unsigned char pad_00[0x5C];
    void (*method)(UnkStruct_0205967c *this, int arg);
};
struct UnkStruct_0205967c {
    VTable *vtable;
};
struct UnkStruct_0205967c_2 {
    unsigned char pad_00[0xCC];
    UnkStruct_0205967c *inner;
};

void func_0205967c(struct UnkStruct_0205967c_2 *self, int arg)
{
    UnkStruct_0205967c *inner = self->inner;
    if (inner != 0) {
        inner->vtable->method(inner, arg);
    }
}
