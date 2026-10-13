/* func_ov003_0223345c @ 0x0223345c, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022353a4(void *a, int b, int c);
extern void func_ov003_02232e88(void *a, void *b);
extern void func_ov003_02233178(void *a, void *b);
extern void func_ov003_02232f78(void *a, void *b);
extern void func_ov003_022333b0(void *a, void *b);

void func_ov003_0223345c(char *self)
{
    char *p = self + 0x242;
    switch (*(unsigned char *) (self + 0x251)) {
        case 4:
        case 0x11:
            func_ov003_022353a4(self, 1, 1);
            func_ov003_02232e88(self, p);
            break;
        case 5:
        case 0xb:
            func_ov003_02233178(self, p);
            break;
        case 9:
            func_ov003_02232f78(self, p);
            break;
        case 0x13:
            func_ov003_022333b0(self, p);
            break;
    }
}
