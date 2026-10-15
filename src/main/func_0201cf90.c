/* func_0201cf90 @ 0x0201cf90, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b;
    int w;
} Params;

void func_0201cf90(int unused, unsigned char *p, int i, unsigned char val, unsigned char b, int w)
{
    p[i * 2] = val;
    *(p + i * 2 + 1) = b;
    *(int *) (p + i * 4 + 12) = w;
}
