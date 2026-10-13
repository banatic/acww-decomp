/* func_0208dd40 @ 0x0208dd40, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vtbl Vtbl;
typedef struct UnkStruct_0208dd40 UnkStruct_0208dd40;

struct Vtbl {
    int unk_00;
    int unk_04;
    void (*func)(UnkStruct_0208dd40 *obj);
};

struct UnkStruct_0208dd40 {
    Vtbl *vtbl;
};

void func_0208dd40(UnkStruct_0208dd40 *obj)
{
    obj->vtbl->func(obj);
}
