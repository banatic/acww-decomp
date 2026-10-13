/* func_020649ac @ 0x020649ac, 0x148 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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

extern void *data_021fbe8c;

extern int FS_ReadFile(UnkStruct_020649ac *f, void *buf, unsigned int n);
extern int func_020e9a3c(void *h, unsigned int v);
extern void *func_020e9948(void *h, unsigned int n);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern void DC_StoreAll(void);
extern void DC_FlushAll(void);
extern void MI_UncompressLZ8(void *buf, void *dst);
extern unsigned int func_020e9dd0(void *h);
extern void MI_InitUncompContextLZ(UnkStruct_020649ac_2 *c, void *dst, void *p);
extern int MI_ReadUncompLZ8(UnkStruct_020649ac_2 *c, void *buf, int n);
extern void func_020e993c(void *h, void *buf);
extern void FS_CloseFile(UnkStruct_020649ac *f);

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
            FS_ReadFile(f, dst, remain);
        } else {
            ret = 0;
        }
        goto end;
    }
    if (FS_ReadFile(f, &hdr, 8) == -1) {
        goto end;
    }
    if (hdr.magic == 0x37375a4c || hdr.magic == 0x4c5a3737) {
        ret = hdr.sz >> 8;
        h = data_021fbe8c;
        saved = func_020e9a3c(h, 0);
        func_020e9a3c(h, saved & 0xffffbfff);
        buf = func_020e9948(h, remain - 4);
        if (buf != 0) {
            MI_CpuCopy8(&hdr.sz, buf, 4);
            DC_StoreAll();
            DC_FlushAll();
            remain -= 8;
            if (FS_ReadFile(f, (char *) buf + 4, remain) != -1) {
                MI_UncompressLZ8(buf, dst);
            }
        } else {
            remain = func_020e9dd0(h);
            buf = func_020e9948(h, remain);
            if (buf != 0) {
                MI_InitUncompContextLZ(&ctx, dst, &hdr.sz);
                do {
                    rr = FS_ReadFile(f, buf, remain);
                    if (rr == -1) {
                        goto done;
                    }
                } while (MI_ReadUncompLZ8(&ctx, buf, rr) != 0);
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
        FS_ReadFile(f, dst, remain);
    } else {
        ret = 0;
    }
end:
    if (f->unk_14 != 0) {
        ret = 0;
    }
    FS_CloseFile(f);
    return ret;
}
