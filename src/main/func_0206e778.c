/* func_0206e778 @ 0x0206e778, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050974(void *p);
extern char data_021c8188;
extern void FS_InitFile(void *buf);
typedef struct {
    void *arc;
    unsigned int file_id;
} FSFileID;
extern int FS_OpenFileFast(void *buf, FSFileID id);
extern void func_02064658(void *buf, int a, int b, int c);
extern int FS_CloseFile(void *buf);

struct UnkStruct_0206e778 {
    FSFileID id;
    int unk_08;
    char pad_0C[12];
    int unk_18;
};

void func_0206e778(void *selfv, unsigned int idx)
{
    struct UnkStruct_0206e778 *self = (struct UnkStruct_0206e778 *) selfv;
    char buf[0x4c];
    unsigned int shifted = idx >> 3;
    func_02050974(&data_021c8188);
    FS_InitFile(buf);
    if (FS_OpenFileFast(buf, self->id) != 0) {
        int scaled = self->unk_08 << 3;
        int mulres = shifted * scaled;
        func_02064658(buf, self->unk_18, scaled, mulres);
        FS_CloseFile(buf);
    }
}
