/* func_ov095_0229c8f0 @ 0x0229c8f0, 0x40 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

/* Jump-table switch on p->mode: cases 1/2/4 call 3-arg handlers, 0/3 fall
   through, then a common func_ov095_022999a8(self, 1). */

typedef struct {
    unsigned char pad_00[22];
    unsigned char mode;
} UnkStruct_0229c8f0;

extern void func_ov095_0229cb5c(UnkStruct_0229c8f0 *self, int b, int c);
extern void func_ov095_0229ca64(UnkStruct_0229c8f0 *self, int b, int c);
extern void func_ov095_0229c974(UnkStruct_0229c8f0 *self, int b, int c);
extern void func_ov095_022999a8(UnkStruct_0229c8f0 *self, int val);

void func_ov095_0229c8f0(UnkStruct_0229c8f0 *self, int b, int c)
{
    switch (self->mode) {
        case 0:
        case 3:
            break;
        case 1:
            func_ov095_0229cb5c(self, b, c);
            break;
        case 2:
            func_ov095_0229ca64(self, b, c);
            break;
        case 4:
            func_ov095_0229c974(self, b, c);
            break;
    }
    func_ov095_022999a8(self, 1);
}
