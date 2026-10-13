/* func_ov114_0229d4c0 @ 0x0229d4c0, 0x40 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1270];
    int a; // 0x1270
    char pad_1274[0x1280 - 0x1274];
    int c; // 0x1280
    char pad_1284[0x1298 - 0x1284];
    int b; // 0x1298
} UnkStruct_0229d4c0;

extern int func_ov114_0229cb7c(UnkStruct_0229d4c0 *self, int arg);
extern void func_ov114_0229cadc(UnkStruct_0229d4c0 *self);

void func_ov114_0229d4c0(UnkStruct_0229d4c0 *self)
{
    int quotient;
    quotient = (self->a * self->b) / 0x8c;
    if (func_ov114_0229cb7c(self, quotient) != 0) {
        func_ov114_0229cadc(self);
    }
    self->c = 0;
}
