/* func_0202a64c @ 0x0202a64c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x830];
    u32 value;
} UnkStruct_0202a64c;

typedef struct {
    u8 pad_00[0x100];
    UnkStruct_0202a64c *inner;
    u8 data[0x1e];
    u8 flag;
} Big;

typedef struct {
    void *data;
    u8 flag;
} UnkStruct_0202a64c_2;

extern void func_0208150c(u32 arg);
extern int func_020036e8(void);
extern void func_0200368c(u8 *dest, u32 size, u32 src, int arg);
extern u32 data_020c8b20;

void func_0202a64c(Big *p, UnkStruct_0202a64c_2 *out)
{
    int ret;

    func_0208150c(p->inner->value);
    ret = func_020036e8();
    func_0200368c(p->data, 0x1e, data_020c8b20, ret);
    p->flag = 1;
    out->data = p->data;
    out->flag = p->flag;
}
