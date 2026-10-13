/* func_020bb7a0 @ 0x020bb7a0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int, int);

typedef struct {
    char pad_00[0x1524];
    int unk_1524;
    char pad_1528[0x4];
    int unk_152C;
    int unk_1530;
    char pad_1534[0x40];
    int unk_1574;
} UnkStruct_020bb7a0;

void func_020bb7a0(UnkStruct_020bb7a0 *self, int param1)
{
    int flag;
    self->unk_152C = param1;
    if (param1 > self->unk_1524) {
        flag = 0;
        self->unk_1530 = flag;
    } else {
        flag = 1;
        self->unk_1530 = flag;
    }
    self->unk_1574 = func_020644cc(2, flag);
}
