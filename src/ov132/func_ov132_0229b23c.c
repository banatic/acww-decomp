/* func_ov132_0229b23c @ 0x0229b23c, 0x40 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(unsigned char *p);
extern void func_ov132_0229aff8(unsigned char *p);
extern void func_ov132_0229af88(unsigned char *p);
extern void func_ov132_0229b0d0(unsigned char *p);

void func_ov132_0229b23c(unsigned char *p)
{
    if (func_0208e484(p + 0x94) != 0) {
        unsigned char v = p[0x1502];
        if (v == 0) {
            goto case0;
        }
        if (v == 1) {
            goto case1;
        }
        if (v != 2) {
            goto end;
        }
        func_ov132_0229b0d0(p);
        goto end;
    case0:
        func_ov132_0229aff8(p);
        goto end;
    case1:
        func_ov132_0229af88(p);
    end:;
    }
}
