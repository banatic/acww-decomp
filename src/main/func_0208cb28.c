/* func_0208cb28 @ 0x0208cb28, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b45d0(void *p0, void *p1, int p2, int p3, int p4, int p5);
extern void func_02051648(void *p0);
extern void func_02051694(void *p0);

void func_0208cb28(void *self)
{
    if (*(unsigned char *) ((char *) self + 0xa7) != 0) {
        if (*(void **) ((char *) self + 0x30) != 0) {
            int sp0 = 0;
            int sp4 = 1;
            func_020b45d0((char *) self + 0x88, *(void **) ((char *) self + 0xb0), 2, 6, sp0, sp4);
            func_02051648(*(void **) ((char *) self + 0x30));
            func_02051694(*(void **) ((char *) self + 0x30));
            *(unsigned char *) ((char *) self + 0xa7) = 0;
        }
    }
}
