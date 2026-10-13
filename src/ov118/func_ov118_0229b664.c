/* func_ov118_0229b664 @ 0x0229b664, 0x26 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov118_0229b664(void *arg0)
{
    int i;
    char *p;
    char *q;

    p = (char *) arg0 + 0xa0;
    *p = 0;
    q = (char *) arg0 + 0xfc;
    for (i = 0; i < 13; i++) {
        func_02070b84(q + i * 0x6c);
    }
}
