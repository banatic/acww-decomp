/* func_ov129_0229b9a0 @ 0x0229b9a0, 0x38 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int);
extern unsigned char *func_ov127_022996bc(unsigned short);

void func_ov129_0229b9a0(unsigned char *param0)
{
    unsigned char *r0;
    unsigned char r2;
    unsigned char r1;
    unsigned char r0_2;

    func_0200467c(0x881);
    r0 = func_ov127_022996bc(*(unsigned short *) (param0 + 0xaa));
    r2 = *r0;
    r1 = *(param0 + 0xb3);
    if (r2 == r1) {
        r0_2 = *(r0 + 1);
        *(param0 + 0xb3) = r0_2;
    } else {
        *(param0 + 0xb3) = r2;
    }
}
