/* func_ov004_0223d200 @ 0x0223d200, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern void func_020e993c(void *, void *);
typedef struct {
    unsigned char pad_00[0x14];
    void *unk_14;
    unsigned char p2[4];
    void *unk_1C;
} UnkStruct_0223d200;
void func_ov004_0223d200(char *self)
{
    void *h = data_021fbe94;
    void *z0 = 0, *z1 = 0;
    unsigned i;
    for (i = 0; i < 2; i++) {
        UnkStruct_0223d200 *e = (UnkStruct_0223d200 *) (self + i * 4);
        if (e->unk_14 != 0) {
            func_020e993c(h, e->unk_14);
            e->unk_14 = z0;
        }
        if (e->unk_1C != 0) {
            func_020e993c(h, e->unk_1C);
            e->unk_1C = z1;
        }
    }
}
