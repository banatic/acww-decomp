/* cafe_master: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022236f0 @ 0x022236f0, 0x14 bytes, Thumb
 * func_ov004_022236dc @ 0x022236dc, 0x14 bytes, Thumb
 * func_ov004_022236c4 @ 0x022236c4, 0x18 bytes, Thumb
 * func_ov004_022236a8 @ 0x022236a8, 0x1c bytes, Thumb
 * func_ov004_0222367c @ 0x0222367c, 0x2c bytes, Thumb
 * func_ov004_02223654 @ 0x02223654, 0x28 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char sub;
} UnkStruct_02223654;

extern char *data_ov004_022580dc;
extern int func_020164a0(int a, int b);
extern void *func_ov004_02224580(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov004_022546e0[];

char *func_ov004_022236f0(void)
{
    return data_ov004_022580dc + 0x718;
}

char *func_ov004_022236dc(void)
{
    return data_ov004_022580dc + 0x748;
}

unsigned short func_ov004_022236c4(void)
{
    return (unsigned short) ((*(unsigned int **) &data_ov004_022580dc)[0x64] >> 12);
}

int func_ov004_022236a8(void)
{
    return func_020164a0((*(int *) &data_ov004_022580dc) + 0x334, 0);
}

void *func_ov004_0222367c(void *s)
{
    *(void **) s = &data_ov004_022546e0;
    func_ov004_02224580((char *) s + 0x658);
    func_0202ee5c(s);
    func_020edf54(s);
    return s;
}

void *func_ov004_02223654(UnkStruct_02223654 *param)
{
    param->unk_00 = ((char *) data_ov004_022546e0);
    func_ov004_02224580(&param->sub);
    func_0202ee5c(param);
    return param;
}
