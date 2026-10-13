/* func_02068fa0 @ 0x02068fa0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[8];
    int unk_08;
} UnkStruct_02068fa0;

extern int FS_OpenFile(void *arg, int *data);
extern int func_020e98d4(int param);
extern int FS_ReadFile(void *arg, int field, int param);
extern int FS_CloseFile(void *arg);
extern int data_020df0d0;

int func_02068fa0(UnkStruct_02068fa0 *obj, void *arg1)
{
    int v6, v4, v0;

    v6 = FS_OpenFile(arg1, &data_020df0d0);
    obj->unk_08 = func_020e98d4(0x2800);
    if (obj->unk_08 != 0) {
        if (FS_ReadFile(arg1, obj->unk_08, 0x2800) != -1) {
            v4 = 1;
        } else {
            v4 = 0;
        }
    } else {
        v4 = 0;
    }
    v0 = FS_CloseFile(arg1);
    if (v6 != 0 && v4 != 0 && v0 != 0 && obj->unk_08 != 0) {
        return 1;
    }
    return 0;
}
