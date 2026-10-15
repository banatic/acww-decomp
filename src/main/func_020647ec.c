/* func_020647ec @ 0x020647ec, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *arc;
    unsigned int file_id;
} FSFileID;
extern void FS_InitFile(void *p);
extern int FS_OpenFileFast(void *p, FSFileID id);
extern void func_02064658(void *a, int b, int c, int d);
extern int FS_CloseFile(void *p);

void func_020647ec(FSFileID id, int a2, int a3, int a4)
{
    char buf[0x4c];
    FS_InitFile(buf);
    if (FS_OpenFileFast(buf, id)) {
        func_02064658(buf, a2, a3, a4);
        FS_CloseFile(buf);
    }
}
