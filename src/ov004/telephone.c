/* telephone: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022116fc @ 0x022116fc, 0x24 bytes, Thumb
 * func_ov004_022116f8 @ 0x022116f8, 0x4 bytes, Thumb
 * func_ov004_022116c4 @ 0x022116c4, 0x34 bytes, Thumb
 */

struct UnkStruct_022116fc;

struct UnkStruct_022116fc_2;

struct UnkStruct_022116fc {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_022116fc_2 {
    char pad_00[300];
    struct UnkStruct_022116fc *b;
};

extern int func_ov004_022118bc(struct UnkStruct_022116fc_2 *, int);
extern void func_0203ee08(void *self, void *p);

void func_ov004_022116fc(struct UnkStruct_022116fc_2 *self)
{
    struct UnkStruct_022116fc *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_022118bc(self, 3);
        }
    }
}

int func_ov004_022116f8(void *callbackObject)
{
    return 1;
}

void func_ov004_022116c4(char *self)
{
    void *p = *(void **) (self + 0x12c);
    char *q;

    if (p != 0 && *(int *) ((char *) p + 4) == 0) {
        q = self;
        if (self != 0) {
            q = q + 0xec;
        }
        func_0203ee08(self, q);
        func_ov004_022118bc((struct UnkStruct_022116fc_2 *) self, 4);
    }
}
