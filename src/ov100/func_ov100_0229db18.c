/* func_ov100_0229db18 @ 0x0229db18, 0x58 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2274];
    char sub;
    char pad_2275[0x6AC];
    unsigned char b1;
    char pad_2922;
    unsigned char b2;
} UnkStruct_0229db18;

extern int func_ov002_02209f9c(char *p);
extern int func_ov100_0229d4f4(UnkStruct_0229db18 *self, int index);
extern void func_ov100_0229cecc(UnkStruct_0229db18 *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov094_022999d8(void);
extern void func_ov100_0229d71c(UnkStruct_0229db18 *self, unsigned char arg, int n);
extern void func_ov100_0229ce24(UnkStruct_0229db18 *self);

void func_ov100_0229db18(UnkStruct_0229db18 *self)
{
    if (func_ov002_02209f9c(&self->sub) == 0) {
        if (self->b1 == self->b2) {
            func_ov100_0229d4f4(self, self->b2);
            func_ov100_0229cecc(self);
            func_ov002_02208098((void *) (self), 4);
            func_ov094_022999d8();
        } else {
            func_ov100_0229d71c(self, self->b2, 4);
        }
    } else {
        func_ov100_0229ce24(self);
    }
}
