/* func_ov118_0229ab64 @ 0x0229ab64, 0x7c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_ov118_0229a460(void *, int);
extern void func_ov118_0229afd4(void *, int);
extern void func_ov118_0229b454(void *);
extern void func_ov118_0229b43c(void *);
extern void func_ov118_0229adf0(void *, int);

int func_ov118_0229ab64(unsigned char *a)
{
    unsigned char b0 = data_021f6c58;
    unsigned char b1 = data_021f6c54;
    if ((int) b1 < 0x33 || (int) b1 > 0x4b) {
        return 0;
    }
    if (func_ov118_0229a460(a, 1)) {
        if ((int) b0 < 0xcd || (int) b0 > 0xe5) {
            return 0;
        }
        func_ov118_0229afd4(a, 0);
        func_ov118_0229b454(a);
    } else {
        if ((int) b0 < 0xaa || (int) b0 > 0xc2) {
            return 0;
        }
        func_ov118_0229afd4(a, 0);
        func_ov118_0229b43c(a);
    }
    func_ov118_0229adf0(a, 0);
    a[0xa3] = 0xff;
    return 1;
}
