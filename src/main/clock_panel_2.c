/* clock_panel_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208d69c @ 0x0208d69c, 0x40 bytes, Thumb
 * func_0208d650 @ 0x0208d650, 0x4c bytes, Thumb
 */

struct UnkStruct_0208d69c {
    unsigned char pad_00[0x10];
    unsigned int *unk_10;
};

struct UnkStruct_0208d69c_2 {
    unsigned char pad_00[0x30];
    struct UnkStruct_0208d69c *sub;
    unsigned char pad_34[0x16];
    unsigned char flag;
    unsigned char pad_4B[0x19];
    unsigned int index;
};

typedef struct UnkStruct_0208d650 {
    char pad_00[0x10];
    char *ptr;
} UnkStruct_0208d650;

typedef struct UnkStruct_0208d650_2 {
    char pad_00[0x34];
    UnkStruct_0208d650 *inner;
    char pad_38[0x13];
    unsigned char flag1;
    char pad_4C[0x17];
    unsigned char flag2;
} UnkStruct_0208d650_2;

extern unsigned int data_020d0aac[];
extern void func_02051648(struct UnkStruct_0208d69c *);
extern void func_02051694(struct UnkStruct_0208d69c *);
extern char data_020d0a64[];

/* FAKEMATCH: the same-arm if keeps self->index loaded before the table address; the plain expression loads the address first */
void func_0208d69c(struct UnkStruct_0208d69c_2 *self)
{
    unsigned int index;

    if (self->sub && self->flag) {
        self->flag = 0;
        if (self) {
            index = self->index;
        } else {
            index = self->index;
        }
        self->sub->unk_10 = &data_020d0aac[index];
        func_02051648(self->sub);
        func_02051694(self->sub);
    }
}

void func_0208d650(UnkStruct_0208d650_2 *p)
{
    if (p->inner != 0 && p->flag1 != 0) {
        int flag;
        p->flag1 = 0;
        flag = 0;
        if (p->flag2 >= 12) {
            flag = 1;
        }
        p->inner->ptr = data_020d0a64 + 6 * flag;
        func_02051648((struct UnkStruct_0208d69c *) p->inner);
        func_02051694((struct UnkStruct_0208d69c *) p->inner);
    }
}
