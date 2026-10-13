/* func_ov003_0220e0c4 @ 0x0220e0c4, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_02008258(void *, int);
extern int func_0200fbe0(void *);
extern void func_0200d4e8(void *, int, int, int);

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_0220e0c4;

void func_ov003_0220e0c4(UnkStruct_0220e0c4 *self)
{
    unsigned short n;
    if (func_02056f94((char *) self + 0x2d0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        n = 3;
        if (func_0200fbe0(self) == 4) {
            n *= (int) n;
        }
        func_0200d4e8(self, n, 1, -1);
    }
}
