/* func_02015f00 @ 0x02015f00, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b5630(void *);
extern int func_020b4508(void *, int, int);
extern void func_02068404(void *, int, void *);
extern void *func_020b5618(void *);

void func_02015f00(void *r5, int r4, int r6, int r7)
{
    char sp[0x44];

    if (r4 >= 0) {
        func_020b5630(sp);
        func_020b4508(sp, r4, r7);
        func_02068404(*(void **) ((char *) r5 + 0x40), r6, sp);
        func_020b5618(sp);
    }
}
