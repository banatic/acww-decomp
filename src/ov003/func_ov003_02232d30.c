/* func_ov003_02232d30 @ 0x02232d30, 0xa4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02232b68(void *a);
extern void func_ov003_02233178(void *a, void *b);
extern void func_ov003_02232f78(void *a, void *b);
extern void func_ov003_02232c70(void *a);
extern int func_ov003_02232aa0(void *a, void *b);
extern void func_020550e4(void *a, int b);

void func_ov003_02232d30(char *self)
{
    short *p = (short *) (self + 0x242);
    switch (*(unsigned char *) (self + 0x251)) {
        case 4:
        case 0x11:
            func_ov003_02232b68(self);
            break;
        case 0xb:
            if (((unsigned int) *(int *) (self + 0xf4) << 4) >> 16 == 1) {
                func_020550e4(self + 0x50, 0);
            }
            // falls through
        case 5:
            func_ov003_02233178(self, p);
            break;
        case 9:
            func_ov003_02232f78(self, p);
            break;
        case 7:
            func_ov003_02232c70(self);
            break;
        case 0x13:
            func_ov003_02232aa0(self, p);
            if (((unsigned int) *(int *) (self + 0xf4) << 4) >> 16 != 0) {
                func_020550e4(self + 0x50, 0);
            }
            break;
    }
}
