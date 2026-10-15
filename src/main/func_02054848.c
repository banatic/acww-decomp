/* func_02054848 @ 0x02054848, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205510c(void *, int);
extern void func_02054a9c(void *, void *);

void func_02054848(void *arg0, int argument1)
{
    void *r4;
    void *r1;

    r4 = arg0;
    func_0205510c(arg0, (int) argument1);
    r1 = *(void **) ((char *) r4 + 0xb4);
    func_02054a9c(r4, r1);
}
