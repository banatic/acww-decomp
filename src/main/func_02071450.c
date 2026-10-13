/* func_02071450 @ 0x02071450, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a[0x1b];
    unsigned char b[0x1d];
    unsigned char c[0x1d];
    unsigned char d[0xb];
} UnkStruct_02071450;
void func_02071450(UnkStruct_02071450 *p)
{
    unsigned int i;
    for (i = 0; i < 0x1b; i++) {
        p->a[i] = 0;
    }
    for (i = 0; i < 0x1d; i++) {
        p->b[i] = 0;
    }
    for (i = 0; i < 0x1d; i++) {
        p->c[i] = 0;
    }
    for (i = 0; i < 0xb; i++) {
        p->d[i] = 0;
    }
}
