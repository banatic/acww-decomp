/* room_object_body_4: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220ff74 @ 0x0220ff74, 0x30 bytes, Thumb
 * func_ov004_0220ff4c @ 0x0220ff4c, 0x28 bytes, Thumb
 * func_ov004_0220fefc @ 0x0220fefc, 0x50 bytes, Thumb
 */

typedef struct {
    int m[12];
} Mtx43;

extern Mtx43 data_021fbe48;
extern void MTX_MultVec43(void *a, Mtx43 *b, void *c);
extern void *data_ov004_0224fe10;
extern void VEC_Add(int *a, int *b, int *d);

void func_ov004_0220ff74(char *self, void *x, void *y)
{
    data_021fbe48 = *(Mtx43 *) (self + 0x254);
    MTX_MultVec43(y, &data_021fbe48, x);
}

void func_ov004_0220ff4c(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220ff74(
        (char *) self, (void *) a1,
        (void *) ((*(int *) ((char *) &data_ov004_0224fe10 + (*(int *) (self + 0x784) << 2)) + (0xc * (a2 & 0x3)))));
}

void func_ov004_0220fefc(char *self, int *out)
{
    int acc[3];
    int tmp[3];
    unsigned i;

    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
    for (i = 0; i < 4; i++) {
        func_ov004_0220ff4c((char *) self, (int) tmp, i);
        VEC_Add(acc, tmp, acc);
    }
    acc[0] = acc[0] >> 2;
    acc[1] = acc[1] >> 2;
    acc[2] = acc[2] >> 2;
    out[0] = acc[0];
    out[1] = acc[1];
    out[2] = acc[2];
}
