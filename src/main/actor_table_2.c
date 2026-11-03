/* actor_table_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082618 @ 0x02082618, 0x2a bytes, Thumb
 * func_020825e8 @ 0x020825e8, 0x30 bytes, Thumb
 * func_020825d8 @ 0x020825d8, 0x10 bytes, Thumb
 * func_020825c8 @ 0x020825c8, 0x10 bytes, Thumb
 * func_0208259c @ 0x0208259c, 0x2c bytes, Thumb
 */

extern int func_02082654(int arg);
extern int func_02082644(int arg);
extern void *func_020829b8(void *arg0, void *arg1);
extern unsigned char data_021d1d4c[];
extern int func_0208270c(void *param1, void *param2);
extern int func_020829ec(void *ctx, int a, int b);
extern int func_02082740(void *ctx, int a, int b);

void *func_020825d8(void *arg0);
int func_020825c8(void *param);

int func_02082618(int arg1, int arg2)
{
    int result = 0;
    switch (arg1) {
        case 2:
            result = func_02082654(arg2);
            break;
        case 3:
            result = func_02082644(arg2);
            break;
    }
    return result;
}

int func_020825e8(unsigned short *p)
{
    int r = 0;
    int k = (*p & 0xf000) >> 12;
    switch (k) {
        case 0xe:
            r = (int) func_020825d8((void *) p);
            break;
        case 0xd:
            r = func_020825c8((void *) p);
            break;
    }
    return r;
}

void *func_020825d8(void *arg0)
{
    return func_020829b8((void *) data_021d1d4c, arg0);
}

int func_020825c8(void *param)
{
    return func_0208270c((void *) data_021d1d4c, param);
}

int func_0208259c(int a, int b)
{
    int result;
    result = func_020829ec(((char *) data_021d1d4c), a, b);
    if (result != 0) {
        return result;
    }
    return func_02082740(((char *) data_021d1d4c), a, b);
}
