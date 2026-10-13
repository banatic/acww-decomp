/* func_020befa0 @ 0x020befa0, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b[23];
} UnkStruct_020befa0;
typedef struct {
    unsigned char b[28];
} UnkStruct_020befa0_2;

extern const UnkStruct_020befa0 data_020e6100;
extern const UnkStruct_020befa0_2 data_020e6168;

extern int FS_OpenFile(void *p, void *s);
extern int FS_ReadFile(void *p, void *buf, int n);
extern int FS_CloseFile(void *p);

int func_020befa0(void *p)
{
    UnkStruct_020befa0 a;
    UnkStruct_020befa0_2 b;
    int r1, r2, r3, r4, r5, r6;

    a = data_020e6100;
    r1 = FS_OpenFile(p, &a);
    r2 = FS_ReadFile(p, (char *) p + 0x1048, 0x1c0) > 0;
    r3 = FS_CloseFile(p);
    b = data_020e6168;
    r4 = FS_OpenFile(p, &b);
    r5 = FS_ReadFile(p, (char *) p + 0x1208, 0x140) > 0;
    r6 = FS_CloseFile(p);
    return r1 && r2 && r3 && r4 && r5 && r6;
}
