/* func_0206807c @ 0x0206807c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8228(void *);
extern void func_020b45d0(void *, int, int, int);
extern void func_020a8be4(void *, void *);
extern void func_020a89dc(void *, void *);
extern void func_020a8210(void *);

extern char data_020cce80[];

typedef struct {
    char data[0x60];
} SomeObject;

typedef struct {
    int a;
    int b;
    SomeObject inner;
} UnkStruct_0206807c;

typedef struct {
    char pad_00[0x1a64];
    int unk_1A64;
    char pad_1A68[0x10];
    char unk_1A78;
} Some;

char *func_0206807c(Some *self)
{
    UnkStruct_0206807c local;
    func_020a8228(&local.inner);
    local.a = 0;
    local.b = 0;
    func_020b45d0(&local.inner, self->unk_1A64, 2, 6);
    func_020a8be4(&self->unk_1A78, data_020cce80);
    func_020a89dc(&self->unk_1A78, &local.inner);
    func_020a8210(&local.inner);
    return &self->unk_1A78;
}
