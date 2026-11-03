/* rom_file: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02064d14 @ 0x02064d14, 0x8 bytes, Thumb
 * func_02064cf8 @ 0x02064cf8, 0x1c bytes, Thumb
 * func_02064cd8 @ 0x02064cd8, 0x20 bytes, Thumb
 * func_02064b2c @ 0x02064b2c, 0x1ac bytes, Thumb
 * func_02064b18 @ 0x02064b18, 0x14 bytes, Thumb
 * func_02064af4 @ 0x02064af4, 0x24 bytes, Thumb
 * func_020649ac @ 0x020649ac, 0x148 bytes, Thumb
 * func_02064980 @ 0x02064980, 0x2a bytes, Thumb
 * func_02064960 @ 0x02064960, 0x20 bytes, Thumb
 * func_0206493c @ 0x0206493c, 0x24 bytes, Thumb
 * func_0206490c @ 0x0206490c, 0x30 bytes, Thumb
 * func_020648a0 @ 0x020648a0, 0x6c bytes, Thumb
 * func_0206487c @ 0x0206487c, 0x24 bytes, Thumb
 * func_02064858 @ 0x02064858, 0x22 bytes, Thumb
 * func_02064828 @ 0x02064828, 0x2e bytes, Thumb
 * func_020647ec @ 0x020647ec, 0x3a bytes, Thumb
 * func_02064658 @ 0x02064658, 0x194 bytes, Thumb
 * func_0206464c @ 0x0206464c, 0xc bytes, Thumb
 * func_02064640 @ 0x02064640, 0xc bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x14];
    unsigned int unk_14;
    unsigned char pad_18[0x0c];
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned char pad_2C[0x20];
} File;

typedef struct {
    unsigned int magic;
    unsigned int sz;
} Hdr;

typedef struct {
    char b[16];
} UnkStruct_020649ac_2;

typedef struct {
    char pad_00[0x14];
    int unk_14;
    char pad_18[0x24 - 0x18];
    int unk_24;
    int unk_28;
} UnkStruct_020649ac;

typedef struct {
    unsigned char pad_00[0x14];
    unsigned int unk_14;
    unsigned char pad_18[0x0C];
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
} UnkStruct_020648a0;

typedef struct {
    void *arc;
    unsigned int file_id;
} FSFileID;

typedef struct {
    u8 pad_00[0x20];
    int unk_20;
    int unk_24;
    int unk_28;
} UnkStruct_02064658;

extern int FS_LoadOverlay(int target, unsigned int id);
extern void FS_InitFile(void *file);
extern int FS_OpenFile(void *file, const char *path);
extern void func_02001964(void *dst, int src);
extern char data_020de6a4[];
extern void *data_021fbe8c;
extern void *data_021fbe94;
extern void *func_020e9968(void *heap, unsigned int size, int align);
extern void func_020e993c(void *heap, void *p);
extern unsigned int func_020e9a3c(void *g, unsigned int v);
extern void *func_020e9948(void *g, unsigned int size);
extern unsigned int func_020e9dd0(void *g);
extern int FS_ReadFile(File *f, void *dst, unsigned int len);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern void DC_StoreAll(void);
extern void DC_FlushAll(void);
extern void MI_UncompressLZ8(const void *src, void *dst);
extern void MI_InitUncompContextLZ(void *ctx, void *dst, const void *hdr);
extern int MI_ReadUncompLZ8(void *ctx, const void *data, unsigned int len);
extern int func_02064300(void *dst, unsigned int size, const void *src, int param);
extern int FS_SeekFile(UnkStruct_020648a0 *self, int a, int b);
extern int FS_CloseFile(void *ptr);
extern int FS_OpenFileFast(void *p, FSFileID id);
extern u16 data_021cb660[];
extern u16 data_021cb654;
extern u8 data_021cb650;
extern int data_021cb860[];
extern u8 data_021cc860[];
extern int FS_UnloadOverlay(int, int);

int func_020649ac(UnkStruct_020649ac *f, char *dst, unsigned int len);
void func_02064658(UnkStruct_02064658 *f, u8 *dst, int a2, int a3);

int func_02064d14(int target, unsigned int id)
{
    return FS_LoadOverlay(target, id);
}

int func_02064cf8(void *file, const char *path)
{
    FS_InitFile(file);
    return FS_OpenFile(file, path);
}

void func_02064cd8(int unused, int arg)
{
    if (func_02064cf8((void *) unused, (const char *) arg) == 0) {
        func_02001964(data_020de6a4, arg);
    }
}

void *func_02064b2c(int id, void *heap, int align, unsigned int *outSize)
{
    File file;
    unsigned int hdr[2];
    unsigned int ctx[4];
    unsigned int size;
    void *buf = 0;
    unsigned int saved;
    void *g = data_021fbe8c;

    if (heap == 0) {
        heap = data_021fbe94;
    }
    func_02064cd8((int) (&file), id);
    size = file.unk_28 - file.unk_24;
    if (size < 8) {
        buf = func_020e9968(heap, size, align);
        if (buf == 0) {
            goto end;
        }
        FS_ReadFile(&file, buf, size);
        goto end;
    }
    if (FS_ReadFile(&file, hdr, 8) == -1) {
        goto end;
    }
    if (hdr[0] == 0x37375a4c || hdr[0] == 0x4c5a3737) {
        unsigned int unc = hdr[1] >> 8;
        void *tmp;
        buf = func_020e9968(heap, unc, align);
        if (buf == 0) {
            goto end;
        }
        saved = func_020e9a3c(g, 0);
        func_020e9a3c(g, saved & 0xffffbfff);
        tmp = func_020e9948(g, size - 4);
        if (tmp != 0) {
            MI_CpuCopy8(&hdr[1], tmp, 4);
            DC_StoreAll();
            DC_FlushAll();
            size -= 8;
            if (FS_ReadFile(&file, (char *) tmp + 4, size) != -1) {
                MI_UncompressLZ8(tmp, buf);
            }
        } else {
            unsigned int chunk = func_020e9dd0(g);
            tmp = func_020e9948(g, chunk);
            if (tmp != 0) {
                MI_InitUncompContextLZ(ctx, buf, &hdr[1]);
                for (;;) {
                    int n = FS_ReadFile(&file, tmp, chunk);
                    if (n == -1) {
                        break;
                    }
                    if (MI_ReadUncompLZ8(ctx, tmp, n) == 0) {
                        break;
                    }
                }
            }
        }
        if (tmp != 0) {
            func_020e993c(g, tmp);
        }
        func_020e9a3c(g, saved);
        size = unc;
        goto end;
    }
    buf = func_020e9968(heap, size, align);
    if (buf == 0) {
        goto end;
    }
    MI_CpuCopy8(hdr, buf, 8);
    if (FS_ReadFile(&file, (char *) buf + 8, size - 8) == -1) {
        func_020e993c(heap, buf);
        buf = 0;
    }
end:
    if (outSize != 0) {
        *outSize = size;
    }
    if (file.unk_14 != 0 && buf != 0) {
        func_020e993c(heap, buf);
        buf = 0;
    }
    FS_CloseFile((void *) (&file));
    return buf;
}

void *func_02064b18(int a)
{
    int b = 0;
    int c = 4;
    int d = b;
    return func_02064b2c(a, (void *) b, c, (unsigned int *) d);
}

int func_02064af4(const void *a, const void *b, int c)
{
    unsigned char buf[0x4c];
    func_02064cd8((int) buf, (int) a);
    return func_020649ac((UnkStruct_020649ac *) buf, (char *) b, c);
}

int func_020649ac(UnkStruct_020649ac *f, char *dst, unsigned int len)
{
    // DECLS
    void *buf;
    unsigned int remain;
    int ret;
    int rr;
    int saved;
    void *h;
    // ENDDECLS
    Hdr hdr;
    UnkStruct_020649ac_2 ctx;

    remain = f->unk_28 - f->unk_24;
    ret = remain;
    if (remain < 8) {
        if (remain <= len) {
            FS_ReadFile((File *) f, dst, remain);
        } else {
            ret = 0;
        }
        goto end;
    }
    if (FS_ReadFile((File *) f, &hdr, 8) == -1) {
        goto end;
    }
    if (hdr.magic == 0x37375a4c || hdr.magic == 0x4c5a3737) {
        ret = hdr.sz >> 8;
        h = data_021fbe8c;
        saved = (int) func_020e9a3c(h, 0);
        func_020e9a3c(h, saved & 0xffffbfff);
        buf = func_020e9948(h, remain - 4);
        if (buf != 0) {
            MI_CpuCopy8(&hdr.sz, buf, 4);
            DC_StoreAll();
            DC_FlushAll();
            remain -= 8;
            if (FS_ReadFile((File *) f, (char *) buf + 4, remain) != -1) {
                MI_UncompressLZ8((const void *) buf, dst);
            }
        } else {
            remain = func_020e9dd0(h);
            buf = func_020e9948(h, remain);
            if (buf != 0) {
                MI_InitUncompContextLZ((void *) (&ctx), dst, (const void *) (&hdr.sz));
                do {
                    rr = FS_ReadFile((File *) f, buf, remain);
                    if (rr == -1) {
                        goto done;
                    }
                } while (MI_ReadUncompLZ8((void *) (&ctx), (const void *) buf, rr) != 0);
            }
        }
    done:
        if (buf != 0) {
            func_020e993c(h, buf);
        }
        func_020e9a3c(h, saved);
        goto end;
    }
    if (remain <= len) {
        MI_CpuCopy8(&hdr, dst, 8);
        dst = dst + 8;
        remain -= 8;
        FS_ReadFile((File *) f, dst, remain);
    } else {
        ret = 0;
    }
end:
    if (f->unk_14 != 0) {
        ret = 0;
    }
    FS_CloseFile((void *) f);
    return ret;
}

void *func_02064980(void *a, void *b, void *c, void *d, int e)
{
    unsigned char buffer[0x80];

    func_02064300(buffer, 0x80, d, e);
    return func_02064b2c((int) buffer, (void *) a, (int) b, (unsigned int *) c);
}

void *func_02064960(int a, int b, int c, ...)
{
    int *p = (int *) (((unsigned int) &c & ~3U) + 4);
    return func_02064980((void *) a, (void *) b, 0, (void *) c, (int) p);
}

void *func_0206493c(const char *fmt, ...)
{
    char *ap;
    ap = (char *) (((unsigned int) &fmt) & ~3u) + 4;
    return func_02064980(0, (void *) 4, 0, (void *) fmt, (int) ap);
}

int func_0206490c(void *a, void *b, int c, ...)
{
    char buf[0x80];
    func_02064300(buf, 0x80, (const void *) c, (int) ((void *) (((unsigned int) (char *) &c & ~3) + 4)));
    return func_02064af4((const void *) buf, (const void *) a, (int) b);
}

int func_020648a0(UnkStruct_020648a0 *self)
{
    unsigned int diff = self->unk_28 - self->unk_24;
    if (diff >= 8) {
        unsigned int r6 = self->unk_2C - self->unk_24;
        unsigned int buf[2];
        FS_SeekFile(self, 0, 0);
        if (FS_ReadFile((File *) self, buf, 8) == -1) {
            goto ret_neg1;
        }
        if (buf[0] == 0x37375a4c || buf[0] == 0x4c5a3737) {
            diff = buf[1] >> 8;
        }
        FS_SeekFile(self, r6, 0);
    }
    if (self->unk_14 != 0) {
        diff = -1;
    }
    return diff;
ret_neg1:
    return -1;
}

int func_0206487c(void *src)
{
    char buf[0x48];
    int result;

    func_02064cd8((int) buf, (int) src);
    result = func_020648a0((UnkStruct_020648a0 *) buf);
    FS_CloseFile(buf);
    return result;
}

int func_02064858(int arg0)
{
    char buffer[72];
    int result;
    result = func_02064cf8(buffer, (const char *) arg0);
    if (result) {
        FS_CloseFile(buffer);
    }
    return result;
}

void func_02064828(void *r0, void *r1, void *r2, void *r3)
{
    char sp[0x4c];

    func_02064cd8((int) sp, (int) r0);
    func_02064658((UnkStruct_02064658 *) sp, (u8 *) r1, (int) r2, (int) r3);
    FS_CloseFile(sp);
}

void func_020647ec(FSFileID id, int a2, int a3, int a4)
{
    char buf[0x4c];
    FS_InitFile(buf);
    if (FS_OpenFileFast(buf, id)) {
        func_02064658((UnkStruct_02064658 *) buf, (u8 *) a2, a3, a4);
        FS_CloseFile(buf);
    }
}

/* FAKEMATCH: the empty if on w keeps the header word's shift before the compressed/plain choice; without it the compare and the shift swap */
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

    FS_SeekFile((UnkStruct_020648a0 *) f, 0, 0);
    if (FS_ReadFile((File *) f, hdr, 8) == -1) {
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
        FS_ReadFile((File *) f, (char *) data_021cb660 + 2, sz);
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
                FS_SeekFile((UnkStruct_020648a0 *) f, n + off, 0);
                FS_ReadFile((File *) f, data_021cb860, len);
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
        FS_SeekFile((UnkStruct_020648a0 *) f, a3, 0);
        FS_ReadFile((File *) f, dst, a2);
    }
}

void func_0206464c(int param)
{
    func_02064d14(0, param);
}

void func_02064640(int a)
{
    FS_UnloadOverlay(0, a);
}
