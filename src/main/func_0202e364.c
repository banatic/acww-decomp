/* func_0202e364 @ 0x0202e364, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201bdb4(void *);
extern void func_0202e58c(void *);
extern int func_020644cc(int);
extern void func_0201cd5c(void *);
extern void func_0201cde8(void *);

int func_0202e364(void *r0)
{
    void *r4 = r0;
    if (func_0201bdb4(r4) == 0) {
        return 0;
    }
    func_0202e58c(r4);
    *(int *) ((char *) r4 + 0x644) = 0;
    *(char *) ((char *) r4 + 0x824) = (char) func_020644cc(2);
    func_0201cd5c((char *) r4 + 0x83c);
    func_0201cde8(r4);
    return 1;
}
