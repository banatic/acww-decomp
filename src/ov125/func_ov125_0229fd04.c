/* func_ov125_0229fd04 @ 0x0229fd04, 0x38 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207cf8(void *);
extern void func_ov002_02207d24(void *, int);

void func_ov125_0229fd04(void *r0)
{
    unsigned char r2;
    void *r1;

    r2 = *(unsigned char *) ((char *) r0 + 0x87c);
    if (r2 <= 7) {
        *(unsigned char *) ((char *) r0 + 0x87a) = r2;
        func_ov002_02207cf8((char *) r0 + 0x574);
    } else {
        func_ov002_02207d24((char *) r0 + 0x574, 1);
    }
}
