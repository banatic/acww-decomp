/* func_0209d2dc @ 0x0209d2dc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    void *unk_04;
} UnkStruct_0209d2dc;

extern void *func_020ea0e0(unsigned int, int);
extern int func_02055c80(UnkStruct_0209d2dc *, int, int, int);

int func_0209d2dc(UnkStruct_0209d2dc *self, int a, int b, int c, int d)
{
    if (c) {
        self->unk_04 = func_020ea0e0((c + 3) & ~3, d);
    }
    if (a || b) {
        self = self + 1;
        if (func_02055c80(self, a, 0, b)) {
            return 1;
        } else {
            return 0;
        }
    }
    return 1;
}
