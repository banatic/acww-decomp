/* func_020b36c8 @ 0x020b36c8, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned short unk_10;
    unsigned short unk_12;
} UnkStruct_020b36c8;

extern unsigned int data_020d1e90[];
extern int func_020e895c(UnkStruct_020b36c8 *self, unsigned int a, unsigned int b);

void func_020b36c8(UnkStruct_020b36c8 *self)
{
    if (self->unk_0C == 1) {
        if (self->unk_12 != 0) {
            self->unk_00 = 0;
            self->unk_12--;
        }
        if (self->unk_12 != 0) {
            return;
        }
        if (self->unk_10 < 0xb) {
            self->unk_00 = data_020d1e90[self->unk_10];
            self->unk_10++;
        } else {
            self->unk_0C = 0;
            self->unk_10 = 0;
        }
    } else {
        if (self->unk_04 != self->unk_00) {
            func_020e895c(self, self->unk_04, self->unk_08);
        }
    }
}
