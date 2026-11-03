/* block_020b220c: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b22f4 @ 0x020b22f4, 0xc bytes, Thumb
 * func_020b22e8 @ 0x020b22e8, 0xc bytes, Thumb
 * func_020b22dc @ 0x020b22dc, 0xc bytes, Thumb
 * func_020b22d0 @ 0x020b22d0, 0xc bytes, Thumb
 * func_020b22c4 @ 0x020b22c4, 0xc bytes, Thumb
 * func_020b22b8 @ 0x020b22b8, 0xc bytes, Thumb
 * func_020b22ac @ 0x020b22ac, 0xc bytes, Thumb
 * func_020b22a0 @ 0x020b22a0, 0xc bytes, Thumb
 * func_020b220c @ 0x020b220c, 0x94 bytes, Thumb
 */

extern unsigned char data_021f4b1c;
extern unsigned char data_021f4b18;
extern unsigned int data_021f4b48;
extern int func_020b65c4(void);
extern int func_020b67e8(int v);
extern int func_020b6694(int v);
extern void __register_global_object(void *, void *, void *);
extern void func_0206e9ec(void *a, int b);
extern void func_020012dc(void *);
extern int data_021f4b54;
extern int data_021f4b7c[3];
extern int data_021f4b64;

void func_020b22f4(void)
{
    (*(char *) &data_021f4b1c) = 1;
}

void func_020b22e8(void)
{
    data_021f4b1c = 0;
}

unsigned char func_020b22dc(void)
{
    return data_021f4b1c;
}

void func_020b22d0(void)
{
    data_021f4b18 = 1;
}

void func_020b22c4(void)
{
    unsigned char *p;
    p = &data_021f4b18;
    *p = 0;
}

unsigned char func_020b22b8(void)
{
    return data_021f4b18;
}

void func_020b22ac(unsigned int value)
{
    data_021f4b48 = value;
}

int func_020b22a0(void)
{
    return (*(int *) &data_021f4b48);
}

void func_020b220c(void)
{
    int v = func_020b65c4();
    int r = -1;

    if (func_020b67e8(v) != 0 || func_020b6694(v) != 0) {
        r = 0;
    } else if (v == 0x1a) {
        r = 1;
    } else if (v == 9) {
        r = 2;
    } else if (v == 10) {
        r = 3;
    }

    if (r != -1) {
        if ((data_021f4b54 & 1) == 0) {
            data_021f4b7c[0] = 0x10000;
            data_021f4b7c[1] = 0;
            data_021f4b7c[2] = 0x1e000;
            __register_global_object((void *) (data_021f4b7c), (((void *) func_020012dc)), (void *) (&data_021f4b64));
            data_021f4b54 |= 1;
        }
        func_0206e9ec(data_021f4b7c, r);
    }
}
