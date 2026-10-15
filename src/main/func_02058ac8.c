/* func_02058ac8 @ 0x02058ac8, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020cbaec[];
extern void func_0205967c(void *a, void *b);
extern void VEC_Add(void *a, void *b, void *c);
extern int func_020e895c(unsigned int *p, int zero, unsigned int val);

typedef struct UnkStruct_02058ac8 {
    unsigned char pad_00[0x60];
    unsigned char unk_60[0x24];
    unsigned char unk_84[0x24];
    unsigned int unk_A8;
    unsigned int unk_AC;
    unsigned int unk_B0;
    unsigned char pad_B4[0xC];
    unsigned int unk_C0;
    unsigned char pad_C4[0x10];
    unsigned char unk_D4;
    unsigned char pad_D5;
    unsigned short unk_D6;
} UnkStruct_02058ac8;

void func_02058ac8(UnkStruct_02058ac8 *self)
{
    if (self->unk_D6 < data_020cbaec[self->unk_D4]) {
        unsigned int temp = self->unk_A8;
        unsigned int val;

        func_020e895c(&temp, 0, self->unk_C0);
        val = temp;
        self->unk_A8 = val;
        self->unk_AC = val;
        self->unk_B0 = val;

        func_0205967c(self, (unsigned char *) self + 0x60);
        VEC_Add((unsigned char *) self + 0x60, (unsigned char *) self + 0x84, (unsigned char *) self + 0x60);

        self->unk_D6++;
        if (self->unk_D6 >= data_020cbaec[self->unk_D4]) {
            self->unk_D4++;
        }
    }
}
