/* field_actor_states_28: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200d58c @ 0x0200d58c, 0x20 bytes, Thumb
 * func_0200d554 @ 0x0200d554, 0x36 bytes, Thumb
 * func_0200d548 @ 0x0200d548, 0xc bytes, Thumb
 * func_0200d53c @ 0x0200d53c, 0xc bytes, Thumb
 * func_0200d530 @ 0x0200d530, 0xc bytes, Thumb
 * func_0200d52c @ 0x0200d52c, 0x2 bytes, Thumb
 * func_0200d528 @ 0x0200d528, 0x4 bytes, Thumb
 */

extern int func_0200d900(int a);
extern void func_0200d5ac(int a, int *b);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

void func_0200d58c(int a)
{
    int x = 0;
    x = func_0200d900(a);
    func_0200d5ac(a, &x);
}

int func_0200d554(int param0, int param1, int param2)
{
    int stack[8];
    int result;

    func_0200e92c(stack);
    func_0200e90c(stack, 1, param1, param2);
    result = func_0200e894((void *) param0, stack);
    func_0200e91c(stack);
    return result;
}

// placeholder for the literal address
void func_0200d548(unsigned int *base, void *message, int previous)
{
    base[0x1fe] = 0;
}

void func_0200d53c(int a, int b)
{
    func_0200d554(a, 9, b);
}

void func_0200d530(void *r0)
{
    *(unsigned int *) ((char *) r0 + 0x7f8) = 1;
}

void func_0200d52c(void *object) {}

void func_0200d528(unsigned short *p0, int p1)
{
    p0[0] = p1;
}
