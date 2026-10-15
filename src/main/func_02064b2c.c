/* func_02064b2c @ 0x02064b2c, 0x1ac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x14];
    unsigned int unk_14;
    unsigned char pad_18[0x0c];
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned char pad_2C[0x20];
} File;

extern void *data_021fbe8c;
extern void *data_021fbe94;

extern void func_02064cd8(File *f, int id);
extern void *func_020e9968(void *heap, unsigned int size, int align);
extern void func_020e993c(void *heap, void *p);
extern unsigned int func_020e9a3c(void *g, unsigned int v);
extern void *func_020e9948(void *g, unsigned int size);
extern unsigned int func_020e9dd0(void *g);
extern int FS_ReadFile(File *f, void *dst, unsigned int len);
extern int FS_CloseFile(File *f);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern void DC_StoreAll(void);
extern void DC_FlushAll(void);
extern void MI_UncompressLZ8(const void *src, void *dst);
extern void MI_InitUncompContextLZ(void *ctx, void *dst, const void *hdr);
extern int MI_ReadUncompLZ8(void *ctx, const void *data, unsigned int len);

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
    func_02064cd8(&file, id);
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
    FS_CloseFile(&file);
    return buf;
}
