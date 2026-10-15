/* func_ov101_0229d168 @ 0x0229d168, 0x40 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb6];
    unsigned char unk_B6;
    char pad_B7[0x229c - 0xb7];
    char unk_229C;
} UnkStruct_0229d168;

extern int func_0208e484(void *p);
extern int func_ov002_02209f9c(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char c);
extern void func_ov101_0229c28c(void *p, int n);
extern void func_ov101_0229ca00(void *p);

void func_ov101_0229d168(UnkStruct_0229d168 *self)
{
    if (func_0208e484(&self->unk_229C)) {
        func_ov002_02208098(self, self->unk_B6);
    }
    if (func_ov002_02209f9c(&self->unk_229C)) {
        func_ov101_0229c28c(self, 0x20);
        func_ov101_0229ca00(self);
    }
}
