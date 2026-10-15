/* func_ov106_0229de28 @ 0x0229de28, 0x50 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xbb];
    unsigned char flag;
    unsigned char pad_BC[0x22a0 - 0xbc];
    void *unk_22A0;
} UnkStruct_0229de28;

extern int func_0208e484(void *ptr);
extern int func_ov002_02209f9c(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov106_0229c364(UnkStruct_0229de28 *self, int a);
extern void func_ov106_0229c344(UnkStruct_0229de28 *self, int a);
extern void func_ov094_022999c0(void);
extern void func_ov106_0229ce0c(UnkStruct_0229de28 *self);

void func_ov106_0229de28(UnkStruct_0229de28 *self)
{
    if (func_0208e484(&self->unk_22A0) != 0) {
        func_ov002_02208098((void *) (self), self->flag);
    }
    if (func_ov002_02209f9c(&self->unk_22A0) != 0) {
        if (func_ov106_0229c364(self, 0x40) != 0) {
            ((void) (func_ov106_0229c344(self, 0x40)), func_ov094_022999c0());
        }
        func_ov106_0229ce0c(self);
    }
}
