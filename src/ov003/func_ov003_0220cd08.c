/* func_ov003_0220cd08 @ 0x0220cd08, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *a, int *b, void *v);
extern void func_020448b8(int *p);

typedef struct {
    char pad_00[0x5c];
    int pos[3];
    char pad_68[0x98 - 0x68];
    int unk_98;
    char pad_9C[0x8d8 - 0x9c];
    int unk_8D8;
    int unk_8DC;
} UnkStruct_0220cd08;

void func_ov003_0220cd08(UnkStruct_0220cd08 *self)
{
    volatile int a = 0, b = 0;
    unsigned int ok;
    int va;
    int t[2];

    if (self->unk_98 > 0x53f) {
        func_0204f818((int *) &a, (int *) &b, self->pos);
        ok = 0;
        va = a;
        if (a == self->unk_8D8 && b == self->unk_8DC) {
            ok = 1;
        }
        if (ok > 0) {
            self->unk_8D8 = va;
            self->unk_8DC = b;
        } else {
            self->unk_8D8 = va;
            self->unk_8DC = b;
            t[0] = a;
            t[1] = b;
            func_020448b8(t);
        }
    }
}
