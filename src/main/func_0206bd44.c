/* func_0206bd44 @ 0x0206bd44, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206c058(void);
extern void func_0206c2e4(void *, void *);
extern void func_0206c1cc(void *, void *);

void func_0206bd44(void *param)
{
    void *r4 = param;
    *(int *) ((char *) r4 + 0x2c) = 0;
    (void) *(void *volatile *) ((char *) r4 + 0x28);
    func_0206c058();
    func_0206c2e4(*(void **) ((char *) r4 + 0x28), *(void **) ((char *) r4 + 0x5c));
    func_0206c1cc(*(void **) ((char *) r4 + 0x28), *(void **) ((char *) r4 + 4));
    *(char *) ((char *) r4 + 0xd9) = 0;
    *(int *) ((char *) r4 + 0xe0) = 0;
}
