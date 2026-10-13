/* func_02091ce8 @ 0x02091ce8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094c38(void *a, void *b, int c);
extern void MI_CpuCopy8(void *d, void *e, int f);

struct Global {
    char pad_00[16];
    short idx;
};

struct Blk {
    unsigned char v[4];
};

typedef char Table1[12];
typedef char Table2[28];

extern struct Global data_021d5658;
extern Table1 data_020e2bb0[];
extern Table2 data_021d52d8[];

void func_02091ce8(unsigned char *p)
{
    struct Global *g = (struct Global *) &data_021d5658;
    struct Blk buf;

    buf = *(struct Blk *) (p + 4);
    func_02094c38(p, data_020e2bb0[g->idx], 0);
    MI_CpuCopy8(g, data_021d52d8[buf.v[0]], 28);
}
