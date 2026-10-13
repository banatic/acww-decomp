/* func_ov003_0221f1ac @ 0x0221f1ac, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203750c(void *p);
extern void *func_02037608(void *p, int n);
extern int func_02037594(void *p);
extern void func_02055f40(void *p, int a, int b);
extern int func_ov003_0221f144(void *p);

struct UnkStruct_0221f1ac {
    char pad_00[0x9c];
    int unk_9C;
};

struct UnkStruct_0221f1ac_2 {
    int unk_00;
    int unk_04;
    int unk_08;
};

int func_ov003_0221f1ac(struct UnkStruct_0221f1ac *self)
{
    struct UnkStruct_0221f1ac_2 *b;
    int res;

    b = (struct UnkStruct_0221f1ac_2 *) func_02037608(func_0203750c(self), 0x83);
    res = func_02037594(func_0203750c(b));
    self->unk_9C = b->unk_08;
    func_02055f40(self, self->unk_9C, res);
    func_ov003_0221f144(self);
    return 1;
}
