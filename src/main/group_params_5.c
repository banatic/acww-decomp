/* group_params_5: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206fcbc @ 0x0206fcbc, 0xc bytes, Thumb
 * func_0206fcb0 @ 0x0206fcb0, 0xc bytes, Thumb
 * func_0206fca4 @ 0x0206fca4, 0xc bytes, Thumb
 * func_0206fc98 @ 0x0206fc98, 0xc bytes, Thumb
 * func_0206fc8c @ 0x0206fc8c, 0xc bytes, Thumb
 * func_0206fc80 @ 0x0206fc80, 0xc bytes, Thumb
 * func_0206fc6c @ 0x0206fc6c, 0x14 bytes, Thumb
 * func_0206fc58 @ 0x0206fc58, 0x14 bytes, Thumb
 * func_0206fc4c @ 0x0206fc4c, 0xc bytes, Thumb
 * func_0206fc44 @ 0x0206fc44, 0x8 bytes, Thumb
 * func_0206fc1c @ 0x0206fc1c, 0x28 bytes, Thumb
 * func_0206fbf8 @ 0x0206fbf8, 0x24 bytes, Thumb
 * func_0206fbd8 @ 0x0206fbd8, 0x20 bytes, Thumb
 * func_0206fbc0 @ 0x0206fbc0, 0x18 bytes, Thumb
 * func_0206fbb4 @ 0x0206fbb4, 0xc bytes, Thumb
 * func_0206fba8 @ 0x0206fba8, 0xc bytes, Thumb
 * func_0206fb9c @ 0x0206fb9c, 0xc bytes, Thumb
 */

extern void *data_021cfc8c;
extern unsigned char data_021cfc5c;
extern unsigned char data_021cfc48;
extern unsigned char data_021cfc4c;
extern int data_021cfd28;
extern void func_02051bf8(void *a, int b);
extern void func_02051c08(void *a, void *b, int c);
extern int func_02070094(void);
extern int func_0207004c(int);
extern unsigned char data_021cfc50[];

void *func_0206fcbc(void)
{
    return data_021cfc8c;
}

void func_0206fcb0(unsigned int r0)
{
    (*(unsigned int * *) &data_021cfc8c) = (unsigned int *) r0;
}

unsigned char func_0206fca4(void)
{
    return data_021cfc5c;
}

void func_0206fc98(char arg0)
{
    (*(char *) &data_021cfc5c) = arg0;
}

unsigned char func_0206fc8c(void)
{
    return data_021cfc48;
}

void func_0206fc80(unsigned char value)
{
    data_021cfc48 = value;
}

int func_0206fc6c(void)
{
    if (data_021cfc4c == 1) {
        return 1;
    } else {
        return 0;
    }
}

int func_0206fc58(void)
{
    if (data_021cfc4c == 2) {
        return 1;
    }
    return 0;
}

void func_0206fc4c(char r0)
{
    (*(char *) &data_021cfc4c) = r0;
}

int func_0206fc44(void)
{
    return (int) &data_021cfd28;
}

void func_0206fc1c(void *param1, int param2)
{
    func_02051bf8(&data_021cfd28, 0x10);
    func_02051c08(param1, &data_021cfd28, param2);
}

int func_0206fbf8(int a)
{
    if (func_02070094() == 0) {
        return 0;
    } else {
        data_021cfc5c = a;
        return func_0207004c(9);
    }
}

int func_0206fbd8(int a, int b)
{
    if (func_0206fbf8(a)) {
        (*(char *) &data_021cfc48) = b;
        return 1;
    }
    return 0;
}

int func_0206fbc0(void)
{
    int result;
    if (func_02070094() != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_0206fbb4(void)
{
    char *ptr;
    ptr = (char *) data_021cfc50;
    *ptr = 0;
}

void func_0206fba8(char r0)
{
    (*(char *) data_021cfc50) = r0;
}

unsigned char func_0206fb9c(void)
{
    return (*(unsigned char *) data_021cfc50);
}
