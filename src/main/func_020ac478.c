/* func_020ac478 @ 0x020ac478, 0x72 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[4];
    unsigned char *unk_04;
    char pad_08[0xc];
    unsigned int unk_14;
} UnkStruct_020ac478;

extern void func_020ac89c(void *dest, unsigned int size);

void func_020ac478(UnkStruct_020ac478 *self, unsigned int idx, unsigned int count)
{
    int a, b, c;
    int j;
    unsigned short v;
    unsigned char *p;

    if (self->unk_14 >= 13) {
        return;
    }
    a = 13 - self->unk_14;
    b = (30 - a) << 1;
    c = (31 - a) << 1;
    while (idx <= count) {
        p = self->unk_04;
        v = *(unsigned short *) (p + idx * 64 + 0x3c);
        *(unsigned short *) ((unsigned int) b + (unsigned int) p + idx * 64) = v;
        p = self->unk_04;
        v = *(unsigned short *) (p + idx * 64 + 0x3e);
        *(unsigned short *) ((unsigned int) c + (unsigned int) p + idx * 64) = v;
        j = a - 1;
        while (j >= 0) {
            func_020ac89c(self->unk_04 + idx * 64 + (31 - j) * 2, 2);
            j--;
        }
        idx++;
    }
}
