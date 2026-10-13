/* func_ov147_0229a4b4 @ 0x0229a4b4, 0xc4 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void FS_InitFile(void *file);
extern void *func_ov147_0229a58c(int size);
extern void func_ov147_0229a578(void *p);
extern void func_ov147_0229a48c(void *file, const char *path, void *buf);
extern void func_ov147_0229a420(void *buf);
extern void func_ov147_0229a468(void *file, const char *path, void *buf);
extern void func_ov147_0229a404(void *buf);
extern void func_ov147_0229a440(void *file, const char *path, void *buf);
extern void func_ov147_0229a3e4(void *buf);

typedef struct {
    char b[0x4c];
} FSFile;

void func_ov147_0229a4b4(int idx)
{

    char path1[28] = "/a_mes/a_mes_ttl_bg_ncg.bin";
    const char *tbl[2] = {"/a_mes/a_mes_ttl_a0_bg_nsc.bin", "/a_mes/a_mes_ttl_b0_bg_nsc.bin"};
    char path2[28] = "/a_mes/a_mes_ttl_bg_ncl.bin";
    FSFile file;

    void *p;

    FS_InitFile(&file);

    p = func_ov147_0229a58c(0x9e0);
    if (p != 0) {
        func_ov147_0229a48c(&file, path1, p);
        func_ov147_0229a420(p);
        func_ov147_0229a578(p);
    }
    p = func_ov147_0229a58c(0x20);
    if (p != 0) {
        func_ov147_0229a468(&file, path2, p);
        func_ov147_0229a404(p);
        func_ov147_0229a578(p);
    }
    p = func_ov147_0229a58c(0x800);
    if (p != 0) {
        func_ov147_0229a440(&file, tbl[idx], p);
        func_ov147_0229a3e4(p);
        func_ov147_0229a578(p);
    }
}
