/* func_020117f8 @ 0x020117f8, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011c88(void *self, int a);
extern int FS_OpenFile(void *self, int id);
extern int func_020e98d4(int size);
extern int FS_SeekFile(void *self, int ptr, int a3);
extern int FS_ReadFile(void *self, int ptr, int size);
extern int FS_CloseFile(void *self);
extern int data_020c8098;

struct UnkStruct_020117f8 {
    char pad_00[0x4c];
    int unk_4C;
};

int func_020117f8(struct UnkStruct_020117f8 *self, int count)
{
    int id;
    int b;
    int flag;
    int local8 = 0, local4 = 0, localC = 0, local10 = 0;
    int ptr;
    unsigned int i;
    int d;

    if (count != 0) {
        id = (int) &data_020c8098;
    } else {
        id = func_02011c88(self, 4);
    }

    b = FS_OpenFile(self, id);
    self->unk_4C = func_020e98d4(0x200);

    flag = 1;
    if (count != 0) {
        ptr = 0x200;
    } else {
        ptr = 0x2300;
    }
    i = 0;
    goto loop_test;

loop_body:
    if (FS_SeekFile(self, ptr, local4) == 0) {
        flag = local8;
    }
    if (FS_ReadFile(self, self->unk_4C + (i << 8), 0x100) == ~local10) {
        flag = localC;
    }
    i++;
    ptr = ptr + 0x400;

loop_test:
    if (i < 2) {
        goto loop_body;
    }

    d = FS_CloseFile(self);

    return (b != 0 && flag != 0 && d != 0) ? 1 : 0;
}
