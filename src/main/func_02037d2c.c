/* func_02037d2c @ 0x02037d2c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    void *unk_24;
} Owner;

extern int func_02037c78(void *obj, int b, int c);

int func_02037d2c(Owner *self, int b, int c)
{
    int result;

    result = 0;
    if (self->unk_24 != 0) {
        result = func_02037c78(self->unk_24, b, c);
    }
    return result;
}
