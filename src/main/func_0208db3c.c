/* func_0208db3c @ 0x0208db3c, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ec98(void);
extern int func_020960f8(int, int);
extern int func_02070070(void);
extern int func_0206fd04(void);
extern int func_0206fd10(void);

typedef struct {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x4e - 0x28];
    unsigned char unk_4E;
} UnkStruct_0208db3c;

int func_0208db3c(UnkStruct_0208db3c *param)
{
    int ret;
    int flag1, flag2, flag3, a1, c1, a2, b1, b2;
    ret = param->unk_4E;
    if (ret != 0) {
        a1 = func_0203ec98();
        c1 = func_020960f8(2, 4);
        a2 = func_02070070();
        flag1 = 0;
        if (a1 != 0 && a2 == 0) {
            flag1 = 1;
        }
        flag2 = 0;
        if (a2 == 0 && c1 == 0) {
            flag2 = 1;
        }
        flag3 = 0;
        if (a1 != 0 && a2 != 0) {
            b1 = func_0206fd04();
            b2 = func_0206fd10();
            if (b1 != 0) {
                if (b2 < 0x1000) {
                    flag3 = 1;
                }
            } else {
                flag3 = 1;
            }
        }
        if (flag1 || flag2 || flag3) {
            ret = 0;
            if (flag1 || flag2) {
                param->unk_24 = 0x1e;
            } else {
                param->unk_24 = 1;
            }
        }
    } else {
        param->unk_24 = 0xa;
    }
    return ret;
}
