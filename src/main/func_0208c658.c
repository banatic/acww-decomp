/* func_0208c658 @ 0x0208c658, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208c658;

typedef int (*VtableFunc)(struct UnkStruct_0208c658 *);

struct Vtable {
    VtableFunc funcs[4];
};

struct UnkStruct_0208c658 {
    struct Vtable *vtable;
};

int func_0208c658(struct UnkStruct_0208c658 *self)
{
    return self->vtable->funcs[3](self);
}
