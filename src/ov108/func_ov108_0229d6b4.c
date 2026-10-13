/* func_ov108_0229d6b4 @ 0x0229d6b4, 0x48 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int AOSS_FD_SET(void *);
extern int func_ov108_0229c404(void *, unsigned char, int);
extern int func_ov002_02208098(void *, int);

struct BigStruct {
    char pad_00[0x2ad];
    unsigned char b_at_0x2ad;
    char pad_2AE[8];
    unsigned char b_at_0x2b6;
    char pad_2B7[0x20f9];
    char obj_at_0x23b0;
};

void func_ov108_0229d6b4(struct BigStruct *self)
{
    if (AOSS_FD_SET(&self->obj_at_0x23b0)) {
        if (self->b_at_0x2b6 != 0) {
            self->b_at_0x2b6--;
        } else {
            func_ov108_0229c404(self, self->b_at_0x2ad, 1);
            func_ov002_02208098(self, 2);
        }
    }
}
