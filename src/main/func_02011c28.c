/* func_02011c28 @ 0x02011c28, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011cd8(void *p);
extern int FS_OpenFile(void *p, int val);
extern void *func_020e98d4(int size);
extern int FS_ReadFile(void *p, void *addr, int size);
extern int FS_CloseFile(void *p);

struct UnkStruct_02011c28 {
    char pad_00[0x48];
    void *unk_48;
};

int func_02011c28(struct UnkStruct_02011c28 *p)
{
    int flag;
    int ret;
    int last;

    ret = FS_OpenFile(p, func_02011cd8(p));
    p->unk_48 = func_020e98d4(0x180);

    if (p->unk_48 != 0) {
        flag = (FS_ReadFile(p, p->unk_48, 0x180) != -1);
    } else {
        flag = 0;
    }

    last = FS_CloseFile(p);

    if (ret && flag && last && p->unk_48 != 0) {
        return 1;
    } else {
        return 0;
    }
}
