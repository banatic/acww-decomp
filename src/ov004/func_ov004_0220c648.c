/* func_ov004_0220c648 @ 0x0220c648, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e895c(void *dst, int c, int n);
extern void func_020ee470(void *self);
extern void func_ov004_0220fefc_unk(void *self, void *local);
extern void func_ov004_0220e61c_unk(void *self, void *local);

void func_ov004_0220c648(void *self)
{
    char local[0x10];
    int *p150;
    int *p158;

    p150 = (int *) ((char *) self + 0x150);
    p158 = (int *) ((char *) self + 0x158);

    func_020e895c((char *) self + 0x150, 0, 0x400);

    *p158 = *p150;
    *((int *) ((char *) self + 0x154)) = *p158;

    if (*p150 == 0) {
        func_020ee470(self);
    }

    if (*(unsigned short *) ((char *) self + 0x770) == 1) {
        func_ov004_0220fefc_unk(self, local);
        func_ov004_0220e61c_unk(self, local);
    }

    (*(unsigned short *) ((char *) self + 0x770))++;
}
