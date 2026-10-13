/* func_02011bc8 @ 0x02011bc8, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011c88(void *, int);
extern int FS_OpenFile(void *, int);
extern int func_020e98d4(int);
extern int FS_ReadFile(void *, int, int);
extern int FS_CloseFile(void *);

struct UnkStruct_02011bc8 {
    char pad_00[0x4c];
    int unk_4C;
};

int func_02011bc8(struct UnkStruct_02011bc8 *self)
{
    int b, flag, d;
    b = FS_OpenFile(self, func_02011c88(self, 4));
    self->unk_4C = func_020e98d4(0x3000);
    if (self->unk_4C != 0) {
        flag = FS_ReadFile(self, self->unk_4C, 0x3000) != -1;
    } else {
        flag = 0;
    }
    d = FS_CloseFile(self);
    if (b != 0 && flag != 0 && d != 0 && self->unk_4C != 0) {
        return 1;
    } else {
        return 0;
    }
}
