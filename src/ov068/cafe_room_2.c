/* cafe_room_2: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0227504c @ 0x0227504c, 0x30 bytes, Thumb
 * func_ov068_02275010 @ 0x02275010, 0x3c bytes, Thumb
 */

typedef struct {
    char pad_00[0x298];
    unsigned char flag;
    char pad_299[0x354 - 0x299];
    char unk_354;
    char pad_355[0x3f8 - 0x355];
    char unk_3F8;
} UnkStruct_02275010;

extern void func_0205510c(void *, int);
extern void func_ov004_0222c598(void *ptr);
extern void func_ov004_0222c5b4(void *a, void *b);
extern int data_ov068_022788b0;

int func_ov068_0227504c(void *self)
{
    func_0205510c((char *) self + 0xec, 0);
    if (((unsigned char *) self)[0x298] != 0) {
        func_0205510c((char *) self + 0x29c, 0);
    }
    return 1;
}

int func_ov068_02275010(UnkStruct_02275010 *self)
{
    func_ov004_0222c598(self);
    if (self->flag) {
        func_ov004_0222c5b4(&self->unk_354, &self->unk_3F8);
    }
    data_ov068_022788b0 = 0;
    return 1;
}
