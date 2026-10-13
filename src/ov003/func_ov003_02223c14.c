/* func_ov003_02223c14 @ 0x02223c14, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055210(void *);
extern void func_020f5958(void *);

void *func_ov003_02223c14(void *p)
{
    int *q;
    func_02055210((char *) p + 8);
    *(int *) ((char *) p + 0xcc) = 0;
    *(int *) ((char *) p + 0xd0) = 0;
    func_020f5958((char *) p + 0xe0);
    q = (int *) ((char *) p + 0x120);
    do {
        q[0] = 0;
        q[1] = 0;
        q += 2;
    } while (q != (int *) ((char *) p + 0x138));
    return p;
}
