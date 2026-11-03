/* villager_talk_10: 2 functions, module main
 * mwccarm 1.2/base -O4,p
 * func_0201e734 @ 0x0201e734, 0x84 bytes, Thumb
 * func_0201e698 @ 0x0201e698, 0x9c bytes, Thumb
 */

#include "types.h"

struct GlobalInfo {
    void *ptr;
    unsigned char unk_04;
};

typedef struct {
    u32 word;
    u8 byte;
} UnkStruct_0201e698;

typedef struct {
    void *ptr;
    u8 byte;
} UnkStruct_0201e698_2;

extern void func_0209e474(void *);
extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *, void *, void *, int, int, void *, int, int, int);
extern struct GlobalInfo data_020c8b50;

void func_0201e734(void *a, void *b)
{
    struct {
        unsigned char byte0;
        unsigned char byte1;
        unsigned char byte2;
        unsigned char byte3;
        unsigned int word4;
    } local;
    int r4;
    int val1;
    int val2;
    void *p;
    *(unsigned int *) &local.byte0 = 0;
    local.word4 = 0;

    func_0209e474(&local);
    if ((unsigned int) local.byte2 < 12) {
        r4 = 0;
    } else if ((unsigned int) local.byte2 < 17) {
        r4 = 2;
    } else {
        r4 = 4;
    }

    p = *(void **) ((char *) a + 0x100);
    val2 = *(int *) ((char *) p + 0x830);

    val1 = func_020036e8((unsigned char *) func_0208150c(val2));

    func_0202da38(a, (char *) a + 0x104, (char *) a + 0x122, 30, val1, data_020c8b50.ptr, 1, r4, data_020c8b50.unk_04);

    *(void **) b = (char *) a + 0x104;
    *((unsigned char *) b + 4) = *((unsigned char *) a + 0x122);
}

void func_0201e698(u8 *self, UnkStruct_0201e698_2 *out)
{
    u32 buf[2];
    int ret;
    int tmp;

    buf[0] = 0;
    buf[1] = 0;

    func_0209e474((void *) buf);

    if (((u8 *) buf)[2] < 0x17u || (((u8 *) buf)[2] == 0x17u && ((u8 *) buf)[1] < 0x1eu)) {
        ret = 6;
    } else if (((u8 *) buf)[1] < 0x37u) {
        ret = 8;
    } else if (((u8 *) buf)[1] < 0x3bu) {
        ret = 10;
    } else {
        ret = 12;
    }

    tmp = func_020036e8((unsigned char *) ((int) func_0208150c(*(u32 *) ((char *) (*(u32 **) (self + 0x100)) + 0x830))));

    func_0202da38(self, self + 0x104, self + 0x122, 0x1e, tmp, (void *) ((*(UnkStruct_0201e698 *) &data_020c8b50).word), 1, ret, (*(UnkStruct_0201e698 *) &data_020c8b50).byte);

    out->ptr = self + 0x104;
    out->byte = self[0x122];
}
