/* func_02081ba0 @ 0x02081ba0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205195c(void *);
extern void func_020a8874(void *, void *, int);

void func_02081ba0(void *r0, void *r1)
{
    void *r5 = r0;
    void *r4 = r1;

    func_0205195c(r4);
    func_020a8874(r4, (char *) r5 + 0x2a, 0xa);
}
