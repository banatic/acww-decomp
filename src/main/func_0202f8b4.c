/* func_0202f8b4 @ 0x0202f8b4, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202f8b4(void *a, void *b);

void func_0202f8b4(void *a, void *b)
{
    unsigned int *p1 = (unsigned int *) a;
    unsigned int *p2 = (unsigned int *) b;
    unsigned int temp;

    temp = *p1 + *p2;
    *p1 = temp;
    temp = *(p1 + 1) + *(p2 + 1);
    *(p1 + 1) = temp;
}
