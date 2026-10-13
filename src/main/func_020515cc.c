/* func_020515cc @ 0x020515cc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020515cc(void *obj, unsigned char a, unsigned char b, unsigned int c, unsigned int d, unsigned char e,
                   unsigned char f, unsigned int g, unsigned int h)
{
    ((unsigned char *) obj)[0x3a] = a;
    ((unsigned char *) obj)[0x3b] = b;
    ((unsigned int *) ((unsigned char *) obj + 0x40))[0] = c;
    ((unsigned int *) ((unsigned char *) obj + 0x44))[0] = d;
    ((unsigned char *) obj)[0x3c] = e;
    ((unsigned char *) obj)[0x3d] = f;
    ((unsigned int *) ((unsigned char *) obj + 0x48))[0] = g;
    ((unsigned int *) ((unsigned char *) obj + 0x4c))[0] = h;
}
