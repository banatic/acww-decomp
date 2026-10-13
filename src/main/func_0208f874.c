/* func_0208f874 @ 0x0208f874, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0208f874_2 UnkStruct_0208f874;
typedef void *(*FuncPtr)(UnkStruct_0208f874 *);

struct UnkStruct_0208f874_2 {
    struct _Vtbl *vtbl;
};

struct _Vtbl {
    int unk_00;
    int unk_04;
    int unk_08;
    FuncPtr func;
};

void *func_0208f874(UnkStruct_0208f874 *self)
{
    return self->vtbl->func(self);
}
