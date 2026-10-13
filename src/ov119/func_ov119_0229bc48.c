/* func_ov119_0229bc48 @ 0x0229bc48, 0x2a bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned char flag;
} UnkStruct_0229bc48;

extern int func_020eae80(unsigned char byte);
extern void func_ov119_0229a410(UnkStruct_0229bc48 *self, int arg);
extern void func_ov119_0229a714(UnkStruct_0229bc48 *self);
extern void func_ov119_0229bbe4(UnkStruct_0229bc48 *self);

void func_ov119_0229bc48(UnkStruct_0229bc48 *self)
{
    if (func_020eae80(self->flag)) {
        func_ov119_0229a410(self, 2);
        func_ov119_0229a714(self);
        func_ov119_0229bbe4(self);
    }
}
