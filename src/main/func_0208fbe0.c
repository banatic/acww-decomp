/* func_0208fbe0 @ 0x0208fbe0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Object Object;

typedef struct VTable {
    int (*func0)(Object *);
    int (*func4)(Object *);
    int (*func8)(Object *);
} VTable;

struct Object {
    VTable *vtable;
};

int func_0208fbe0(Object *self)
{
    return self->vtable->func8(self);
}
