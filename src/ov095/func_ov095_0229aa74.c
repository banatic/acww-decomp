/* func_ov095_0229aa74 @ 0x0229aa74, 0x38 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229ab68(void);
extern void func_ov095_0229aae0(void);
extern void func_ov095_0229aaac(void);

int func_ov095_0229aa74(unsigned char *p0)
{
    switch (p0[0x16]) {
        case 0:
        case 3:
            break;
        case 1:
            func_ov095_0229ab68();
            break;
        case 2:
            func_ov095_0229aae0();
            break;
        case 4:
            func_ov095_0229aaac();
            break;
    }
}
