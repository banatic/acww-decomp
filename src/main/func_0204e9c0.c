/* func_0204e9c0 @ 0x0204e9c0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e97c(void *base, int *out, int *in);

void *func_0204e9c0(void *base, int *src)
{
    int out[2];
    int in[2];
    void *result;

    out[0] = 0;
    out[1] = 0;
    in[0] = src[0];
    in[1] = src[1];

    result = 0;
    if (func_0204e97c(base, out, in)) {
        result = (char *) base + 0x2024 + (out[1] << 7) + (out[0] << 5);
    }
    return result;
}
