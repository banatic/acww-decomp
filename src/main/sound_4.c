/* sound_4: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200459c @ 0x0200459c, 0x10 bytes, Thumb
 * func_0200458c @ 0x0200458c, 0x10 bytes, Thumb
 * func_0200457c @ 0x0200457c, 0x10 bytes, Thumb
 * func_0200456c @ 0x0200456c, 0x10 bytes, Thumb
 * func_0200455c @ 0x0200455c, 0x10 bytes, Thumb
 * func_0200454c @ 0x0200454c, 0x10 bytes, Thumb
 * func_0200453c @ 0x0200453c, 0x10 bytes, Thumb
 * func_0200452c @ 0x0200452c, 0x10 bytes, Thumb
 */

extern void func_020f0edc(void *a, void *b);
extern unsigned char data_021fd1bc[];
extern void func_020f0f48(void *param1, void *param2);
extern int func_020f0f34(void *receiver, void *value);
extern void func_020f0ea8(int, int);
extern void func_020f0e74(void *a, void *b);
extern void *func_020f0e60(void *ptr);
extern void func_020f0e48(void *arg0);
extern void func_020f0e34(void *ptr);

void func_0200459c(void *arg0)
{
    void *local = arg0;
    func_020f0edc((void *) data_021fd1bc, local);
}

void func_0200458c(void *param1)
{
    func_020f0f48((void *) data_021fd1bc, param1);
}

int func_0200457c(void *param1)
{
    return func_020f0f34(data_021fd1bc, param1);
}

void func_0200456c(int p0)
{
    func_020f0ea8((int) ((int *) data_021fd1bc), p0);
}

void func_0200455c(void *arg0)
{
    func_020f0e74((void *) data_021fd1bc, arg0);
}

void func_0200454c(void)
{
    func_020f0e60((void *) data_021fd1bc);
}

void func_0200453c(void)
{
    func_020f0e48((void *) data_021fd1bc);
}

void func_0200452c(void)
{
    func_020f0e34((void *) data_021fd1bc);
}
