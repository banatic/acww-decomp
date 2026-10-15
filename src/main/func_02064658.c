/* func_02064658 @ 0x02064658, 0x194 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if on w keeps the header word's shift before the compressed/plain choice; without it the compare and the shift swap */

#include "types.h"

typedef struct {
    u8 pad_00[0x20];
    int unk_20;
    int unk_24;
    int unk_28;
} UnkStruct_02064658;

extern int FS_SeekFile(UnkStruct_02064658 *f, int pos, int mode);
extern int FS_ReadFile(UnkStruct_02064658 *f, void *dst, int n);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern void MI_UncompressLZ8(const void *src, void *dst);

extern u16 data_021cb660[];
extern u16 data_021cb654;
extern u8 data_021cb650;
extern int data_021cb860[];
extern u8 data_021cc860[];

void func_02064658(UnkStruct_02064658 *f, u8 *dst, int a2, int a3)
{
    unsigned int n;
    unsigned int last;
    int len;
    int cnt;
    int end;
    unsigned int t2;
    unsigned int t1;
    union {
        unsigned int all;
        struct {
            unsigned int b0 : 4;
            unsigned int b1 : 4;
            unsigned int b2 : 24;
        } f;
    } hdr[2];
    unsigned int blk;
    unsigned int i;
    unsigned int v;
    int off;
    unsigned int w;
    u16 *q;
    unsigned int sz;
    unsigned int usz;
    int s;
    int u;
    unsigned int wf;

    FS_SeekFile(f, 0, 0);
    if (FS_ReadFile(f, hdr, 8) == -1) {
        return;
    }
    if (hdr[0].all == 0x37375a4c || hdr[0].all == 0x4c5a3737) {
        v = hdr[1].all;
        if ((v & 0xf0) != 0xf0) {
            return;
        }
        if ((unsigned int) (f->unk_28 - f->unk_24) > 0xffff) {
            return;
        }
        blk = 0x20 << hdr[1].f.b0;
        data_021cb660[0] = 0;
        sz = ((v >> 8) - 1) / blk;
        sz = (sz + 1) * 2;
        FS_ReadFile(f, (char *) data_021cb660 + 2, sz);
        n = sz + 8;
        end = a3 + a2;
        last = (end - 1) / blk + 1;
        for (i = a3 / blk; i < last; i++) {
            t1 = blk;
            t1 = t1 * (i + 1);
            if ((unsigned int) a3 >= t1) {
                continue;
            }
            t2 = blk;
            t2 = t2 * i;
            if ((unsigned int) end <= t2) {
                continue;
            }
            if (f->unk_20 != data_021cb654 || i != data_021cb650) {
                data_021cb654 = (u16) f->unk_20;
                data_021cb650 = (u8) i;
                q = &data_021cb660[i];
                off = data_021cb660[i];
                len = q[1] - off;
                FS_SeekFile(f, n + off, 0);
                FS_ReadFile(f, data_021cb860, len);
                w = data_021cb860[0];
                wf = w & 0xf0;
                w >>= 8;
                if (!w && !w) {
                }
                if (wf == 0) {
                    MI_CpuCopy8((char *) data_021cb860 + 4, data_021cc860, w);
                } else {
                    MI_UncompressLZ8(data_021cb860, data_021cc860);
                }
            }
            s = a3 - t2;
            if (s < 0) {
                s = 0;
            }
            u = t1 - end;
            if (u < 0) {
                u = 0;
            }
            cnt = blk - s - u;
            MI_CpuCopy8(data_021cc860 + s, dst, cnt);
            dst = dst + cnt;
        }
    } else {
        FS_SeekFile(f, a3, 0);
        FS_ReadFile(f, dst, a2);
    }
}
