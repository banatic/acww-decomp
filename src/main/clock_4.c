/* clock_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209dfc0 @ 0x0209dfc0, 0x18 bytes, Thumb
 * func_0209dfa4 @ 0x0209dfa4, 0x1c bytes, Thumb
 * func_0209df94 @ 0x0209df94, 0x10 bytes, Thumb
 * func_0209df7c @ 0x0209df7c, 0x18 bytes, Thumb
 */

typedef struct {
    int pad_00;
    int a;
    int b;
    int c;
    int d;
} UnkStruct_0209df7c;

extern void RTC_Init(void);
extern void func_0209e49c(int param);
extern unsigned char data_021dc744[];
extern void func_020469f4(void);

void func_0209dfc0(void)
{
    RTC_Init();
    func_0209e49c((unsigned int) data_021dc744);
}

void func_0209dfa4(void *param)
{
    func_0209e49c((int) ((void *) data_021dc744));
    if (param == 0) {
        func_020469f4();
    }
}

void func_0209df94(unsigned char *p0)
{
    p0[0] = ((int *) data_021dc744)[2];
    p0[1] = ((int *) data_021dc744)[1];
}

void func_0209df7c(unsigned char *dst)
{
    dst[0] = (*(UnkStruct_0209df7c *) data_021dc744).c;
    dst[1] = (*(UnkStruct_0209df7c *) data_021dc744).d;
    dst[2] = (*(UnkStruct_0209df7c *) data_021dc744).b;
    dst[3] = (*(UnkStruct_0209df7c *) data_021dc744).a;
}
