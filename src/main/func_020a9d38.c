/* func_020a9d38 @ 0x020a9d38, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef int (*FuncPtr)(void *);
typedef struct Vtbl Vtbl;
struct Vtbl {
    FuncPtr fn0;
    FuncPtr fn1;
    FuncPtr fn2;
    FuncPtr fn3;
    FuncPtr fn4;
};
typedef struct UnkStruct_020a9d38 UnkStruct_020a9d38;
struct UnkStruct_020a9d38 {
    Vtbl *vtable;
};
typedef struct {
    UnkStruct_020a9d38 *ptr;
    unsigned char pad_04[0x260];
    unsigned char flag;
} UnkStruct_020a9d38_2;

void func_020a9d38(UnkStruct_020a9d38_2 *self)
{
    if (self->ptr != 0) {
        self->ptr->vtable->fn2(self->ptr);
        if (self->ptr->vtable->fn4(self->ptr)) {
            self->ptr = 0;
            self->flag = 1;
        }
    } else {
        self->flag = 0;
    }
}
