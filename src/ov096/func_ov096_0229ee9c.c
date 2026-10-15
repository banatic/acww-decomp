/* func_ov096_0229ee9c @ 0x0229ee9c, 0x94 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229ef30(void *a, int b, int c, int d);
extern unsigned short func_ov096_0229f0dc(void *a, void *b);
extern int func_ov096_0229f088(void *a, void *b);
extern int func_ov096_0229defc(void *a, unsigned short *p1, unsigned char c, unsigned short *p2, int x);

int func_ov096_0229ee9c(void *a, void *b, int c)
{
    int ret;
    int ret2;
    unsigned short local0;
    unsigned short local2;
    int r6;

    ret = func_ov096_0229ef30(a, (int) b, *(unsigned short *) ((char *) a + 0xac), *(unsigned char *) ((char *) a + 0xb0));
    if (ret != 0) {
        return ret;
    }

    local0 = (unsigned short) func_ov096_0229f0dc(a, b);
    if (local0 == 0xfff1) {
        return 0;
    }

    r6 = func_ov096_0229f088(a, b);
    if (c == 0x25) {
        local2 = *(unsigned short *) ((char *) a + 0xac);
        ret2 = func_ov096_0229defc(a, &local2, *(unsigned char *) ((char *) a + 0xb0), &local0, r6);
        if (ret2 == 2 || ret2 == 3) {
            return 6;
        }
        if (local0 == 0xfff1) {
            return 0;
        }
    }
    return func_ov096_0229ef30(a, c, (int) local0, r6);
}
