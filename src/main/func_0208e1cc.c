/* func_0208e1cc @ 0x0208e1cc, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e1bc(void *);

void func_0208e1cc(void *r0)
{
    if (*(int *) ((char *) r0 + 0x78) > 2) {
        *(int *) ((char *) r0 + 0x30) -= 6;
    } else {
        *(int *) ((char *) r0 + 0x30) += 2;
    }
    *(int *) ((char *) r0 + 0x78) -= 1;
    if (*(int *) ((char *) r0 + 0x78) <= 0) {
        *(int *) ((char *) r0 + 0x30) = 0;
        func_0208e1bc(r0);
    }
}
