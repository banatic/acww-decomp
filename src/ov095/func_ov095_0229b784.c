/* func_ov095_0229b784 @ 0x0229b784, 0x8c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef unsigned short u16;
typedef unsigned int u32;

extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int size);
extern int func_ov095_0229b9e0(void *self, u16 val, int flag);
extern int func_ov095_0229b704(void *self, void *ptr);

typedef struct {
    u16 data[6];
    u32 n;
    u16 unk_10;
    u16 unk_12;
} UnkStruct_0229b784;

int func_ov095_0229b784(UnkStruct_0229b784 *self, u16 val)
{
    u16 buf[10];
    int ret;

    self->unk_12 = val;
    self->unk_10 = 0;
    if (!func_ov095_0229b9e0(self, val, 0)) {
        return 0;
    }

    if (self->n == 0) {
        return 0;
    }

    MIi_CpuCopy16(self, buf, 12);
    buf[6] = 0;
    buf[self->n] = val;

    ret = func_ov095_0229b704(self, buf);
    if (ret == 0) {
        ret = func_ov095_0229b704(self, &buf[self->n - 1]);
        if (ret != 0) {
            self->unk_12 = ret;
            buf[self->n - 1] = 0;
            ret = func_ov095_0229b704(self, buf);
            if (ret != 0) {
                self->unk_10 = ret;
            }
            return 2;
        }
    } else {
        self->unk_12 = 0;
        self->unk_10 = ret;
        return 1;
    }
    return 0;
}
