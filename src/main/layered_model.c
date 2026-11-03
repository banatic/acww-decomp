/* layered_model: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020541b8 @ 0x020541b8, 0x2e bytes, Thumb
 * func_02054188 @ 0x02054188, 0x2e bytes, Thumb
 * func_02054170 @ 0x02054170, 0x18 bytes, Thumb
 */

extern void func_02054a94(unsigned int, unsigned int);
extern void func_02054a34(unsigned int, unsigned int);
extern void func_020545b0(unsigned int, unsigned int);
extern void func_02054a64(int, unsigned int);
extern void func_02054580(int, unsigned int);

void func_020541b8(unsigned int param0, unsigned int param1, unsigned int param2)
{
    unsigned int i;
    for (i = param1; i <= param2; i++) {
        func_02054a94(param0, i);
        func_02054a34(param0, i);
        func_020545b0(param0, i);
    }
}

void func_02054188(int p1, unsigned int p2, unsigned int p3)
{
    unsigned int i;
    for (i = p2; i <= p3; i++) {
        func_02054a94(p1, i);
        func_02054a64(p1, i);
        func_02054580(p1, i);
    }
}

void func_02054170(void *arg0)
{
    unsigned int *ptr;
    unsigned int val;

    ptr = (unsigned int *) ((char *) arg0 + 0x1b0);
    *ptr = 0;
    val = *ptr;
    *(unsigned int *) ((char *) arg0 + 0x1ac) = val;
}
