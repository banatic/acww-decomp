/* func_ov102_0229d88c @ 0x0229d88c, 0x54 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char);
extern int func_ov002_02209f9c(void *);
extern int func_ov102_0229c2a8(void *, int);
extern void func_ov102_0229c288(void *, int);
extern void func_ov094_022999c0(void);
extern void func_ov102_0229cd38(void *);

typedef struct {
    char pad_00[0x2274];
    char unk_2274;
    char pad_2275[0x332];
    unsigned char unk_25A7;
} UnkStruct_0229d88c;

void func_ov102_0229d88c(UnkStruct_0229d88c *self)
{
    if (func_0208e484(&self->unk_2274) != 0) {
        func_ov002_02208098(self, self->unk_25A7);
    }
    if (func_ov002_02209f9c(&self->unk_2274) != 0) {
        if (func_ov102_0229c2a8(self, 0x40) != 0) {
            func_ov102_0229c288(self, 0x40);
            func_ov094_022999c0();
        }
        func_ov102_0229cd38(self);
    }
}
