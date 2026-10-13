/* func_ov068_0226aec0 @ 0x0226aec0, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226aec0 {
    int pad_00;
};
extern char data_021e5a2c[];
extern int func_0207cf14(struct UnkStruct_0226aec0 *, void *);
extern int func_0207bb84(struct UnkStruct_0226aec0 *, int, int);

int func_ov068_0226aec0(void *a, void *b)
{
    struct UnkStruct_0226aec0 *g;
    int h1;
    int n;
    int r;

    g = (struct UnkStruct_0226aec0 *) data_021e5a2c;
    r = 2;
    if (g != 0) {
        h1 = func_0207cf14(g, a);
        n = func_0207cf14(g, b);
        n = func_0207bb84(g, h1, n);
        if (n < 5) {
            r = n;
        }
    }
    return r;
}
