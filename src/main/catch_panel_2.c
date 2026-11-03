/* catch_panel_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208cc64 @ 0x0208cc64, 0x42 bytes, Thumb
 * func_0208cc44 @ 0x0208cc44, 0x20 bytes, Thumb
 * func_0208cbfc @ 0x0208cbfc, 0x48 bytes, Thumb
 * func_0208cbb8 @ 0x0208cbb8, 0x42 bytes, Thumb
 */

typedef struct {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[0x34 - 0x28];
    char unk_34;
    char pad_35[0xa4 - 0x35];
    unsigned char flag_a4;
    char pad_A5[0xc1 - 0xa5];
    unsigned char unk_C1;
} UnkStruct_0208cbfc;

typedef struct {
    unsigned char pad_00[0x28];
    void *unk_28;
    unsigned char pad_2C[0x24];
    unsigned char unk_50[0x55];
    unsigned char unk_A5;
    unsigned char pad_A6[0x1a];
    unsigned char unk_C0;
} UnkStruct_0208cbb8;

extern void func_020a8fb8(void *object);
extern void func_0208cb70(void *);
extern void func_0208cb28(void *);
extern int func_020b45d0(void *a, unsigned char b, int c, int d, int e, int f);
extern void func_02051624(void *p);
extern void func_02051694(void *p);

void func_0208cbfc(UnkStruct_0208cbfc *self);
void func_0208cbb8(UnkStruct_0208cbb8 *s);

void func_0208cc64(void *p)
{
    if (*(int *) ((char *) p + 0x24) != 0) {
        func_020a8fb8((void *) *(int *) ((char *) p + 0x24));
        *(int *) ((char *) p + 0x24) = 0;
    }
    if (*(int *) ((char *) p + 0x28) != 0) {
        func_020a8fb8((void *) *(int *) ((char *) p + 0x28));
        *(int *) ((char *) p + 0x28) = 0;
    }
    if (*(int *) ((char *) p + 0x2c) != 0) {
        func_020a8fb8((void *) *(int *) ((char *) p + 0x2c));
        *(int *) ((char *) p + 0x2c) = 0;
    }
    if (*(int *) ((char *) p + 0x30) != 0) {
        func_020a8fb8((void *) *(int *) ((char *) p + 0x30));
        *(int *) ((char *) p + 0x30) = 0;
    }
}

void func_0208cc44(void *arg)
{
    func_0208cbfc((UnkStruct_0208cbfc *) arg);
    func_0208cbb8((UnkStruct_0208cbb8 *) arg);
    func_0208cb70(arg);
    func_0208cb28(arg);
}

void func_0208cbfc(UnkStruct_0208cbfc *self)
{
    if (self->flag_a4 == 0) {
        return;
    }
    if (self->unk_24 == 0) {
        return;
    }
    func_020b45d0(&self->unk_34, self->unk_C1, 2, 6, 0, 1);
    func_02051624(self->unk_24);
    func_02051694(self->unk_24);
    self->flag_a4 = 0;
}

void func_0208cbb8(UnkStruct_0208cbb8 *s)
{
    if (s->unk_A5 == 0) {
        return;
    }
    if (s->unk_28 == 0) {
        return;
    }
    func_020b45d0(&s->unk_50, s->unk_C0, 2, 6, 0, 1);
    func_02051694(s->unk_28);
    s->unk_A5 = 0;
}
