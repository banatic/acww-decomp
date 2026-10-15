/* func_0206d650 @ 0x0206d650, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vtbl Vtbl;
typedef struct Object Object;

struct Object {
    Vtbl *vtable;
};

extern Vtbl data_020def64;
extern void *func_020a9a40(Object *this);
extern void func_020edb3c(Object *this);

Object *func_0206d650(Object *this)
{
    this->vtable = &data_020def64;
    func_020a9a40(this);
    func_020edb3c(this);
    return this;
}
