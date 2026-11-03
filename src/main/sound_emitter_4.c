/* sound_emitter_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020044c0 @ 0x020044c0, 0xe bytes, Thumb
 * func_020044b0 @ 0x020044b0, 0xe bytes, Thumb
 * func_020044a0 @ 0x020044a0, 0x10 bytes, Thumb
 * func_02004490 @ 0x02004490, 0x10 bytes, Thumb
 */

typedef struct VTable VTable;

struct VTable {
    unsigned char pad_00[0x10];
    int (*func)(void *self);
};

typedef struct UnkStruct_020044a0 UnkStruct_020044a0;

struct UnkStruct_020044a0 {
    VTable *vtbl;
};

extern int func_020f5748(int a, int b, int c, int d);
extern int func_020f56a4(int a, int b, int c, int d);

int func_020044c0(int a, int b, int c, int d)
{
    return func_020f5748(a, b, c, d);
}

int func_020044b0(int a, int b, int c, int d)
{
    return func_020f56a4(a, b, c, d);
}

int func_020044a0(UnkStruct_020044a0 *self)
{
    return self->vtbl->func(self);
}

void func_02004490(void *self)
{
    void *vtable;
    void (*func)(void *);

    vtable = *(void **) self;
    func = *(void (**)(void *))((char *) vtable + 8);
    func(self);
}
