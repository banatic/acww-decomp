/* func_0208d69c @ 0x0208d69c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the same-arm if keeps self->index loaded before the table address; the plain expression loads the address first */

extern unsigned int data_020d0aac[];
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
extern void func_02051648(struct UnkStruct_0208d69c *);
extern void func_02051694(struct UnkStruct_0208d69c *);

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
