/* sound: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020040b4 @ 0x020040b4, 0x8 bytes, Thumb
 * func_020040ac @ 0x020040ac, 0x8 bytes, Thumb
 * func_020040a4 @ 0x020040a4, 0x8 bytes, Thumb
 * func_0200409c @ 0x0200409c, 0x8 bytes, Thumb
 * func_02004094 @ 0x02004094, 0x8 bytes, Thumb
 * func_0200408c @ 0x0200408c, 0x8 bytes, Thumb
 * func_02004044 @ 0x02004044, 0x48 bytes, Thumb
 * func_0200403c @ 0x0200403c, 0x8 bytes, Thumb
 */

extern void func_020fa034(void *);
extern void func_020f9f74(void *, int);
extern unsigned char func_020f9f98(void);
extern int func_020f9f48(void *);
extern void func_020f6508(void *);
extern void func_020f6350(void *, unsigned short);
extern int data_021c67a4;
extern int data_021c67b8[3];
extern void func_020f61e4(int, int *);
extern void func_020f64c8(void *);

void func_020040b4(void *argument0)
{
    func_020fa034((void *) argument0);
}

void func_020040ac(void *argument0, int argument1)
{
    func_020f9f74((void *) argument0, (int) argument1);
}

unsigned char func_020040a4(char *receiver)
{
    return func_020f9f98();
}

int func_0200409c(void *argument0)
{
    return func_020f9f48((void *) argument0);
}

void func_02004094(void *argument0)
{
    func_020f6508((void *) argument0);
}

void func_0200408c(void *argument0, unsigned short argument1)
{
    func_020f6350((void *) argument0, (unsigned short) argument1);
}

void func_02004044(int arg0, int *arg1)
{
    if (arg1) {
        if (data_021c67a4) {
            int diff[3];
            diff[0] = arg1[0] - data_021c67b8[0];
            diff[1] = arg1[1] - data_021c67b8[1];
            diff[2] = arg1[2] - data_021c67b8[2];
            func_020f61e4(arg0, diff);
        }
    } else {
        func_020f61e4(arg0, arg1);
    }
}

void func_0200403c(void *argument0)
{
    func_020f64c8((void *) argument0);
}
