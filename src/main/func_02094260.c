/* func_02094260 @ 0x02094260, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: copying the first word through the global and the next two through a char alias gives the base-plus-offset stores; plain field copies and a struct copy change the size */

extern unsigned int data_021d5658;
void func_02094260(unsigned int *p, unsigned int v)
{
    unsigned int *q;
    unsigned short *s;
    char *ptr;
    ptr = (char *) (&data_021d5658);
    q = p + 1;
    *q = data_021d5658;
    q[1] = *((unsigned int *) (ptr + 4));
    q[2] = *((unsigned int *) (ptr + 8));
    q = p + 4;
    *q = v;
    q[1] = v;
    q[2] = v;
    s = (unsigned short *) (p + 7);
    *s = 0;
    s[1] = 0;
    s[2] = 0;
}
