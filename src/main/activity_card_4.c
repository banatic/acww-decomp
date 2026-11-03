/* activity_card_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a24ac @ 0x020a24ac, 0x28 bytes, Thumb
 * func_020a2480 @ 0x020a2480, 0x2c bytes, Thumb
 * func_020a2468 @ 0x020a2468, 0x18 bytes, Thumb
 */

extern unsigned char data_020e37f8;
extern void *func_020984e8(void);
extern void *func_0209847c(unsigned char);
extern void MI_CpuCopy8(void *, const void *, unsigned int);
extern char data_021ee418[];
static void func_0209010c(void *);

void func_020a24ac(void *receiver)
{
    void *p1;
    void *p2;

    p1 = func_020984e8();
    p2 = func_0209847c(data_020e37f8);
    MI_CpuCopy8(p1, p2, 0x249c);
}

void func_020a2480(unsigned int *arg)
{
    void *p = data_021ee418;
    func_0209010c(p);
    MI_CpuCopy8(p, (const void *) arg[48], 0x950);
}

void func_020a2468(int p0)
{
    MI_CpuCopy8((void *) (*(int *) ((char *) (((int) (p0) + (192))) + (0))), (const void *) ((int) ((int *) data_021ee418)), 2384);
}
