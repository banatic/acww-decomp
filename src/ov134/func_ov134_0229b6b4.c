/* func_ov134_0229b6b4 @ 0x0229b6b4, 0x26 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *p);

void func_ov134_0229b6b4(void *p)
{
    int i;
    char *q;
    char *r;

    q = (char *) p + 0x9f;
    *q = 0;
    r = (char *) p + 0xd8;
    for (i = 0; i < 17; i++) {
        func_02070b84(r + i * 0x6c);
    }
}
