/* resource_pools_2: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02078da4 @ 0x02078da4, 0x30 bytes, Thumb
 * func_02078d88 @ 0x02078d88, 0x1a bytes, Thumb
 * func_02078d80 @ 0x02078d80, 0x8 bytes, Thumb
 * func_02078d78 @ 0x02078d78, 0x8 bytes, Thumb
 * func_02078d68 @ 0x02078d68, 0x10 bytes, Thumb
 * func_02078d64 @ 0x02078d64, 0x2 bytes, Thumb
 * func_02078d3c @ 0x02078d3c, 0x28 bytes, Thumb
 * func_02078d24 @ 0x02078d24, 0x18 bytes, Thumb
 * func_02078d1c @ 0x02078d1c, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned long a[64];
} UnkStruct_02078d1c;

extern unsigned int func_0205c200(void *);
extern void func_02078c4c(void *);
extern void func_02078b84(void *);
extern void *data_021fbe94;
extern void func_0205c1e0(void);
extern void func_02078c34(void);
extern void func_02078b6c(void);
extern unsigned int func_0205c35c(int);
extern void func_02078cb0(void *ptr);
extern int func_020e9abc(void *);
extern void *data_021c9ac4;
extern void func_02078c88(void *ptr);
extern void func_0205c340(void);
extern unsigned char data_021d12dc[];

void func_02078d3c(int argument0);
void func_02078d24(void);

void func_02078da4(void)
{
    func_0205c200(data_021fbe94);
    func_02078d3c((int) data_021fbe94);
    func_02078c4c(data_021fbe94);
    func_02078b84(data_021fbe94);
}

void func_02078d88(void)
{
    func_0205c1e0();
    func_02078d24();
    func_02078c34();
    func_02078b6c();
}

int func_02078d80(void)
{
    return 11212;
}

int func_02078d78(void)
{
    return 12780;
}

void func_02078d68(int *r0)
{
    int i;
    int *p;

    i = 0;
    do {
        p = &r0[i];
        *p = 0;
        i++;
    } while (i < 5);
}

void func_02078d64(void *object) {}

void func_02078d3c(int argument0)
{
    void *condition_value0;
    func_0205c35c((int) argument0);
    func_02078cb0(((char *) data_021d12dc));
    if ((condition_value0 = (void *) (data_021c9ac4))) {
        func_020e9abc(condition_value0);
    }
}

void func_02078d24(void)
{
    void *ptr;
    ptr = (void *) data_021d12dc;
    func_02078c88(ptr);
    func_0205c340();
}

unsigned long func_02078d1c(UnkStruct_02078d1c *p, int i)
{
    return p->a[i];
}
