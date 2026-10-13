/* func_020138a8 @ 0x020138a8, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(void *, void *, void *);
extern void func_02013440(void *);
extern void func_02012e58(void *, void *);

void func_020138a8(void *r0, void *r1)
{
    int sp0, sp4;
    void *r5 = r0;
    void *r4 = r1;

    sp0 = 0;
    sp4 = 0;
    func_0204f818(&sp0, &sp4, r4);

    if (*(int *) ((char *) r5 + 0x94) != 0 && *(int *) ((char *) r5 + 0x98) != 0) {
        if (*(int *) ((char *) r5 + 0x94) != sp0 || *(int *) ((char *) r5 + 0x98) != sp4) {
            *(int *) ((char *) r5 + 4) = 3;
            func_02013440(r5);
            *(int *) ((char *) r5 + 0x88) = 0;
            *(int *) ((char *) r5 + 0x8c) = 2;
            func_02012e58(r5, r4);
            *(int *) ((char *) r5 + 0x90) = 4;
        }
    }
}
