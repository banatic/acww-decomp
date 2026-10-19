/* func_020f6508 @ 0x020f6508, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f6948(int param);
extern void func_020eed48(void *res);
extern int data_021fd1bc[];
extern int data_021fd268;

typedef struct {
    char unk_00[6];
    signed char unk_06;
    signed char unk_07;
    signed char unk_08;
    signed char unk_09;
    signed char unk_0A;
} UnkStruct_020f6508;

void func_020f6508(UnkStruct_020f6508 *self)
{
    data_021fd268 = func_020f6948(data_021fd1bc[12]);
    func_020eed48((void *) self);
    self->unk_0A = 0;
    self->unk_06 = -1;
    self->unk_07 = 0;
    self->unk_09 = -1;
    self->unk_08 = self->unk_09;
}
