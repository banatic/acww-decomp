/* talk_object_9: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02067a64 @ 0x02067a64, 0x10 bytes, Thumb
 * func_02067a3c @ 0x02067a3c, 0x28 bytes, Thumb
 * func_02067a2c @ 0x02067a2c, 0x10 bytes, Thumb
 * func_020679fc @ 0x020679fc, 0x30 bytes, Thumb
 * func_020679ec @ 0x020679ec, 0x10 bytes, Thumb
 */

extern void func_020a8c1c(int a);
extern void func_02064210(char *, void *);
extern int data_021dc7a8;
extern int func_020984e8(void);
extern int func_02099870(int arg);
extern void *func_02095074(int a, char *ptr);

void func_02067a64(int a)
{
    func_020a8c1c(a + 0x1c8c);
}

int func_02067a3c(char *arg)
{
    func_020a8c1c((int) (arg + 0x1c8c));
    func_02064210((char *) &data_021dc7a8 + 2, arg + 0x1c8c);
    return 1;
}

void func_02067a2c(unsigned int param1)
{
    unsigned int local_var;
    local_var = param1 + 0x1cac;
    func_020a8c1c(local_var);
}

int func_020679fc(char *arg)
{
    int t = func_020984e8();
    func_020a8c1c((int) (arg + 0x1cac));
    func_02095074(func_02099870(t), arg + 0x1cac);
    return 1;
}

void func_020679ec(int arg)
{
    func_020a8c1c(arg + 0x1ccc);
}
