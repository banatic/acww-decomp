/* func_0208dd50 @ 0x0208dd50, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *pad_00;
    void *pad_04;
    void *pad_08;
    void *(*func)(void *);
} VTable;

typedef struct {
    VTable *vtable;
} Object;

void *func_0208dd50(Object *self)
{
    return self->vtable->func(self);
}
