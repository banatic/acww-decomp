/* func_ov055_0226090c @ 0x0226090c, 0x22 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206837c(int arg);
extern int func_020ab504(int arg);
extern void func_02074958(void);

typedef struct UnkStruct_0226090c {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x40 - 0x1f];
    int unk_40;
} UnkStruct_0226090c;

void func_ov055_0226090c(UnkStruct_0226090c *self)
{
    int ret = func_020ab504(func_0206837c(self->unk_40));
    if (self->unk_1E == 0x3a && ret == 1) {
        func_02074958();
    }
}
