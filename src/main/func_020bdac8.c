/* func_020bdac8 @ 0x020bdac8, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void func_02065268(int);
extern void *func_020bdc50(void *, int, int, int, int);

typedef struct {
    char pad_00[0x2f10];
    int unk_2F10;
} UnkStruct_020bdac8;

void func_020bdac8(UnkStruct_020bdac8 *self)
{
    if (self->unk_2F10 <= 0) {
        self->unk_2F10 = 0x32;
    }

    self->unk_2F10 = self->unk_2F10 - 1;
    if (self->unk_2F10 > 0) {
        return;
    }

    if (func_020644cc(8) == 0) {
        func_020bdc50(self, 8, 0x3b, 0, 0);
    }

    func_02065268(0);
    self->unk_2F10 = func_020644cc(0xc8) + 10;
}
