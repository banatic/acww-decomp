/* func_02034898 @ 0x02034898, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02034898 {
    signed short a[3];
    signed short b[3];
    signed short c[3];
    char d;
};

void func_02034898(struct UnkStruct_02034898 *p)
{
    unsigned int i;
    p->d = 0;
    i = 0;
    do {
        p->c[i] = 0;
        p->b[i] = p->c[i];
        p->a[i] = p->b[i];
        i++;
    } while (i < 3);
}
