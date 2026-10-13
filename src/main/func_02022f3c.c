/* func_02022f3c @ 0x02022f3c, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02022f3c {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02022f3c;
typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;
typedef struct UnkStruct_02022f3c_2 {
    char pad_00[0x100];
    UnkStruct_02022f3c *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02022f3c_2;
typedef struct {
    unsigned short unk_00;
    unsigned short pad_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
} Agg;
extern Cfg data_020c8a20;
extern void func_0209e474(void *p);
extern int func_0204fafc(int x);
extern int *func_0204fc3c(int a, int b);
extern int func_0202cb70(Agg *a, int *b, int *c, int *d, int *e);
extern int func_02023010(int x);
extern void func_02015de4(UnkStruct_02022f3c_2 *self, Agg *a, int b, int c);
extern void func_02023040(UnkStruct_02022f3c_2 *self, int a, Agg *b, int c, int d, int e);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern void func_0202da38(UnkStruct_02022f3c_2 *self, char *a, unsigned char *b, int n, int e, int f, int g, int h, int i);
int func_02022f3c(UnkStruct_02022f3c_2 *self)
{
    int ret;
    int *h;
    Agg agg;
    int t;
    ret = 0;
    agg.unk_04 = 0;
    agg.unk_08 = 0;
    agg.unk_0C = 5;
    agg.unk_00 = 0xfff1;
    agg.unk_10 = 0;
    agg.unk_14 = 0;
    func_0209e474(&agg.unk_04);
    t = ((u8 *) (&agg))[8];
    h = func_0204fc3c(t, func_0204fafc(((u8 *) (&agg))[7]));
    if (h != 0) {
        if (func_0202cb70(&agg, &agg.unk_0C, &agg.unk_10, &agg.unk_14, h) == 1) {
            ret = 0;
            if (agg.unk_0C >= 3) {
                ret = 1;
            }
            ret = (ret * 3) + func_02023010(agg.unk_10);
            func_02015de4(self, &agg, 0, 7);
            func_02023040(self, agg.unk_14, &agg, agg.unk_0C, *h, 1);
            func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                          data_020c8a20.unk_00, data_020c8a20.unk_04, ret, 0);
            ret = 1;
        }
    }
    return ret;
}
