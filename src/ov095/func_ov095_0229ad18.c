/* func_ov095_0229ad18 @ 0x0229ad18, 0x78 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088d9c(const void *);
extern int func_02088d94(const void *);
extern int func_ov095_0229ad90(void *, int);
extern int func_ov095_0229cdf0(const void *);
extern int func_ov090_022990b8(int);
extern int data_ov095_0229e380;
extern int data_ov095_0229e814;

struct UnkStruct_0229ad18 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
};

int func_ov095_0229ad18(struct UnkStruct_0229ad18 *p)
{
    if (p->unk_28 == 0xf7) {
        p->unk_2C = func_02088d9c(&data_ov095_0229e380) + 0x98;
        p->unk_30 = func_02088d94(&data_ov095_0229e380) + 0x70;
        return 1;
    }
    if (p->unk_28 >= 268 && p->unk_28 <= 271) {
        p->unk_2C = func_ov095_0229ad90(p, p->unk_28);
        p->unk_30 = func_02088d94(&data_ov095_0229e814) + 0x68;
        return 1;
    }
    if (func_ov095_0229cdf0(p)) {
        p->unk_2C = func_ov090_022990b8(p->unk_28 - 0xfb);
        p->unk_30 = 8;
        return 1;
    }
    return 0;
}
