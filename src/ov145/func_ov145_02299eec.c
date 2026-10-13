/* func_ov145_02299eec @ 0x02299eec, 0x44 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a72c(void *p, int a);
extern int func_ov002_0220a4d4(void *p);

typedef struct {
    unsigned char pad_00[0xc2];
    unsigned char mode;
} Func_ov145_02299eec_Struct;

int func_ov145_02299eec(Func_ov145_02299eec_Struct *self)
{
    if (self->mode <= 3) {
        return 0xAD;
    }
    switch (self->mode) {
        case 4:
            return func_ov002_0220a72c((char *) self + 0x174, 6);
        case 5:
            return func_ov002_0220a4d4((char *) self + 0x12c);
        default:
            return 0x60;
    }
}
