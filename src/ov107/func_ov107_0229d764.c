/* func_ov107_0229d764 @ 0x0229d764, 0x4c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xbc];
    unsigned char unk_BC;
    unsigned char unk_BD;
    unsigned char pad_BE[0x22b4 - 0xbe];
    char unk_22B4[0x2318 - 0x22b4];
    char unk_2318[0x2705 - 0x2318];
    unsigned char table[0x100];
} UnkStruct_0229d764;

extern int func_0208e484(void *);
extern void func_ov002_02209114(void *, unsigned char, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov107_0229d764(UnkStruct_0229d764 *self)
{
    if (func_0208e484(self->unk_22B4)) {
        func_ov002_02209114(self->unk_2318, self->unk_BD, 1);
        self->unk_BC = self->table[self->unk_BD];
        func_ov002_02208098((void *) (self), 12);
    }
}
