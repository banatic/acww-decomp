/* func_0207835c @ 0x0207835c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short func_02077898(const short *p);

typedef struct {
    short arr[4];
    unsigned char ch;
} Src;

void func_0207835c(int *dest, short *out, const Src *src)
{
    int i;
    short *p = out;
    *dest = src->ch;
    for (i = 0; i < 4; i++) {
        *p++ = func_02077898(&src->arr[i]);
    }
}
