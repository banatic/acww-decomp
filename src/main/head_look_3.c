/* head_look_3: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205e8b0 @ 0x0205e8b0, 0x28 bytes, Thumb
 * func_0205e898 @ 0x0205e898, 0x18 bytes, Thumb
 * func_0205e878 @ 0x0205e878, 0x20 bytes, Thumb
 * func_0205e86c @ 0x0205e86c, 0xc bytes, Thumb
 * func_0205e860 @ 0x0205e860, 0xc bytes, Thumb
 * func_0205e854 @ 0x0205e854, 0xc bytes, Thumb
 * func_0205e848 @ 0x0205e848, 0xc bytes, Thumb
 * func_0205e83c @ 0x0205e83c, 0xc bytes, Thumb
 */

extern unsigned int func_0205c65c(int);
extern void func_0205e5ec(void *arg);
extern int data_021c9f5c;
extern int data_021c9ae4;
extern int func_020e9abc(void *);
extern void func_0205e568(void *arg);
extern void func_0205c640(void);
extern int func_02064328(void *a, void *b, unsigned int c, unsigned int d);
extern char data_021c9f48[];
extern char data_020dd738[];
extern unsigned char data_020cc820[];
extern unsigned char data_020cc830[];
extern unsigned char data_020cc878[];
extern unsigned char data_020cc858[];
extern unsigned char data_020cc840[];

void func_0205e8b0(int argument0)
{
    void *condition_value0;
    func_0205c65c((int) argument0);
    func_0205e5ec(&data_021c9f5c);
    if ((condition_value0 = (void *) (data_021c9ae4)) != 0) {
        func_020e9abc(condition_value0);
    }
}

void func_0205e898(void)
{
    func_0205e568(((char *) &data_021c9f5c));
    func_0205c640();
}

void *func_0205e878(unsigned int a)
{
    func_02064328(data_021c9f48, data_020dd738, a >> 5, a);
    return data_021c9f48;
}

unsigned char func_0205e86c(unsigned int r0)
{
    return data_020cc820[r0];
}

unsigned char func_0205e860(unsigned char r0)
{
    return data_020cc830[r0];
}

unsigned char func_0205e854(unsigned int r0)
{
    return data_020cc878[r0];
}

unsigned char func_0205e848(unsigned int r0)
{
    return data_020cc858[r0];
}

unsigned char func_0205e83c(unsigned int r0)
{
    return data_020cc840[r0];
}
