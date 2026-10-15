/* func_ov003_0221a128 @ 0x0221a128, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x26C];
    int unk_26C;
    int unk_270;
    char pad_274[0x30];
    char unk_2A4;
    char pad_2A5[0x3B];
    unsigned char unk_2E0;
    char pad_2E1[0x97];
    unsigned short unk_378;
} UnkStruct_0221a128;

extern int func_0208a020(char *);
extern int func_ov003_0221abf8(void *object);
extern int func_0203e0a8(UnkStruct_0221a128 *, int);

void func_ov003_0221a128(UnkStruct_0221a128 *self)
{
    self->unk_270 = self->unk_26C;
    if (self->unk_2E0 != 0) {
        int ret = func_0208a020(&self->unk_2A4);
        if (ret != 0 && *(int *) ((char *) ret + 0x98) > 0x666) {
            // clang-format off
            asm {
                mov r0, self
                mov r1, #1
                bl func_ov003_0221abf8
            }
            // clang-format on
            return;
        }
    }
    if ((((unsigned int) self->unk_378 << 23) >> 31) != 0) {
        func_0203e0a8(self, 0);
    }
}
