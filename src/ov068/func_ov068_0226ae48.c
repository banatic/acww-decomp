/* func_ov068_0226ae48 @ 0x0226ae48, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021e5a2c;
extern int func_ov068_0226aec0(int, int);
extern void func_0207bae8(void *, int, int, int);

void func_ov068_0226ae48(int unused, int a, int b, signed char *indices)
{
    void *p = (void *) &data_021e5a2c;
    if (p) {
        int ret = func_ov068_0226aec0(a, b);
        if (ret < 5) {
            func_0207bae8(p, a, b, indices[ret]);
        }
    }
}
