/* func_ov054_02262310 @ 0x02262310, 0x58 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
typedef struct {
    unsigned int v;
    unsigned int pad[2];
} Tbl12;
extern Tbl12 data_ov054_022629e0[], data_ov054_022629e8[];
extern int func_02019d0c(void *a, int b, int c, unsigned int d, unsigned int e, int f, int g, int h, int i, int j, int k);

struct UnkStruct_02262310 {
    unsigned char pad[0x80c];
    unsigned int idx;
};

int func_ov054_02262310(struct UnkStruct_02262310 *self)
{
    unsigned int idx = self->idx;
    func_02019d0c((char *) self + 0x564, 6, 1, data_ov054_022629e0[idx].v, data_ov054_022629e8[idx].v, 0x800, 0, 0, 0,
                  data_020c80f8, 0);
    return 1;
}
