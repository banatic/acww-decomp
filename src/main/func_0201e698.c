/* func_0201e698 @ 0x0201e698, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern void func_0209e474(u32 *p);
extern int func_0208150c(u32 v);
extern int func_020036e8(int v);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

typedef struct {
    u32 word;
    u8 byte;
} UnkStruct_0201e698;
extern UnkStruct_0201e698 data_020c8b50;

typedef struct {
    void *ptr;
    u8 byte;
} UnkStruct_0201e698_2;

void func_0201e698(u8 *self, UnkStruct_0201e698_2 *out)
{
    u32 buf[2];
    int ret;
    int tmp;

    buf[0] = 0;
    buf[1] = 0;

    func_0209e474(buf);

    if (((u8 *) buf)[2] < 0x17u || (((u8 *) buf)[2] == 0x17u && ((u8 *) buf)[1] < 0x1eu)) {
        ret = 6;
    } else if (((u8 *) buf)[1] < 0x37u) {
        ret = 8;
    } else if (((u8 *) buf)[1] < 0x3bu) {
        ret = 10;
    } else {
        ret = 12;
    }

    tmp = func_020036e8(func_0208150c(*(u32 *) ((char *) (*(u32 **) (self + 0x100)) + 0x830)));

    func_0202da38(self, self + 0x104, self + 0x122, 0x1e, tmp, data_020c8b50.word, 1, ret, data_020c8b50.byte);

    out->ptr = self + 0x104;
    out->byte = self[0x122];
}
