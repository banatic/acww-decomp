/* func_02039f30 @ 0x02039f30, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fd10(void);
extern int func_0206fd34(void);
extern int FX_MulFunc(int, int);

typedef struct {
    char pad_00[0xc];
    int flag;
    char pad_10[0x40];
    int result;
} UnkStruct_02039f30;

void func_02039f30(UnkStruct_02039f30 *s)
{
    int flag = s->flag;
    if (flag == 0) {
        int t = func_0206fd10();
        int a = FX_MulFunc(0x4c000, t);
        int b = FX_MulFunc(0xc0000, 0x1000 - t);
        s->result = (a + b) >> 12;
    } else {
        int t = func_0206fd34();
        int a = FX_MulFunc(-0x5c000, t);
        int b = FX_MulFunc(0x30000, 0x1000 - t);
        s->result = (a + b) >> 12;
    }
}
