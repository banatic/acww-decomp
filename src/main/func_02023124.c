/* func_02023124 @ 0x02023124, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02023124 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02023124;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02023124_2 {
    char pad_00[0x100];
    UnkStruct_02023124 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02023124_2;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    unsigned short unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
} Agg;

extern Cfg data_020c8b88;
extern int data_020d9f84;

extern void func_0209e474(void *p);
extern int func_0202d060(unsigned short *a, int *b, int *c, int *d, void *e);
extern int func_0202c9c0(int x);
extern void func_02015de4(UnkStruct_02023124_2 *self, unsigned short *a, int b, int c);
extern void func_02015dd4(UnkStruct_02023124_2 *self, int n, Agg *a, void *tbl, u8 *e);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern void func_0202da38(UnkStruct_02023124_2 *self, char *a, unsigned char *b, int n, int e, int f, int g, int h, int i);

int func_02023124(UnkStruct_02023124_2 *self)
{
    // DECLS
    int ret;
    Agg agg;
    // ENDDECLS

    ret = 0;
    agg.unk_04 = 0;
    agg.unk_08 = 0;
    agg.unk_0C = 5;
    agg.unk_02 = 0xfff1;
    agg.unk_10 = 0;
    agg.unk_14 = 0;
    func_0209e474(&agg.unk_04);
    if (func_0202d060(&agg.unk_02, &agg.unk_0C, &agg.unk_10, &agg.unk_14, &agg.unk_04) == 1) {
        if (agg.unk_0C >= 3) {
            ret = 1;
        }
        ret = ret * 3 + func_0202c9c0(agg.unk_10);
        func_02015de4(self, &agg.unk_02, 0, 7);
        if (agg.unk_14 >= 3) {
            agg.unk_14 = agg.unk_14 - 1;
        }
        agg.unk_00 = agg.unk_14;
        agg.unk_01 = 0;
        func_02015dd4(self, 3, &agg, &data_020d9f84, &agg.unk_01);
        func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                      data_020c8b88.unk_00, data_020c8b88.unk_04, ret, 0);
        ret = 1;
    }
    return ret;
}
