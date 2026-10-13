/* func_02069004 @ 0x02069004, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FS_OpenFile(int, void *);
extern int func_020e98d4(int);
extern int FS_ReadFile(int, int, int);
extern int FS_CloseFile(int);

typedef struct {
    int pad_00;
    int unk_04;
} UnkStruct_02069004;

extern unsigned char data_020df0e8[];

int func_02069004(UnkStruct_02069004 *s, int param1)
{
    int v6;
    int flag;
    int v4;

    v6 = FS_OpenFile(param1, (void *) data_020df0e8);
    s->unk_04 = func_020e98d4(0x180);
    if (s->unk_04 != 0) {
        int ret = FS_ReadFile(param1, s->unk_04, 0x180);
        flag = 0;
        if (ret != -1) {
            flag = 1;
        }
    } else {
        flag = 0;
    }

    v4 = FS_CloseFile(param1);
    if (v6 != 0 && flag != 0 && v4 != 0 && s->unk_04 != 0) {
        return 1;
    }
    return 0;
}
