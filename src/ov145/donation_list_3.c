/* donation_list_3: 2 functions, module ov145
 * mwccarm 1.2/base -O4,s
 * func_ov145_02299e90 @ 0x02299e90, 0x40 bytes, Thumb
 * func_ov145_02299e60 @ 0x02299e60, 0x30 bytes, Thumb
 */

typedef struct {
    char pad_00[0xc2];
    unsigned char flag;
    char pad_C3[5];
    char unk_C8;
} UnkStruct_02299e90;

extern void func_ov002_0220a314(void *ptr);
extern void func_ov002_0220a2b4(void *ptr);
extern int func_ov145_02299f30(UnkStruct_02299e90 *self);
extern int func_ov145_02299eec(UnkStruct_02299e90 *self);
extern void func_ov002_0220a05c(void *a, int b, int c, int d, int e);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov145_02299e60(void *self, int p1, int p2);

void func_ov145_02299e90(UnkStruct_02299e90 *self)
{
    int v1;
    int v2;
    if (self->flag == 4) {
        func_ov002_0220a314(&self->unk_C8);
    } else {
        func_ov002_0220a2b4(&self->unk_C8);
    }
    v1 = func_ov145_02299f30(self);
    v2 = func_ov145_02299eec(self);
    func_ov145_02299e60((void *) self, v1, v2);
}

void func_ov145_02299e60(void *self, int p1, int p2)
{
    func_ov002_0220a05c((unsigned char *) self + 0xc8, p1, p2, 3, 1);
    *((unsigned char *) self + 0xc3) = *((unsigned char *) self + 0x8d);
    func_ov002_02208098((void *) (self), 6);
}
