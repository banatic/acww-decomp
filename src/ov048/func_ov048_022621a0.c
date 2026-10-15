/* func_ov048_022621a0 @ 0x022621a0, 0x28 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov048_022609fc(void *receiver);
extern void func_0206844c(int a, char *b, int c);
extern int data_ov048_02263d20;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_022621a0;

void func_ov048_022621a0(UnkStruct_022621a0 *self)
{
    char tmp;
    tmp = func_ov048_022609fc(self);
    func_0206844c(self->unk_40, &tmp, data_ov048_02263d20);
}
