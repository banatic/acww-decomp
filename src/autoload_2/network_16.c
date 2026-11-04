/* network_16: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ed17c @ 0x020ed17c, 0x18 bytes, ARM
 * func_020ed168 @ 0x020ed168, 0x14 bytes, ARM
 * func_020ed144 @ 0x020ed144, 0x24 bytes, ARM
 */

typedef struct {
    unsigned short value;
    unsigned char flag;
} Unk_020ed144;

extern int data_021fbf48;
extern int data_021fbf50;
extern Unk_020ed144 data_021fbff8[];

void func_020ed17c(int arg, void *user_data)
{
    if (arg == 0) {
        data_021fbf48 = 1;
    }
}

void func_020ed168(void)
{
    data_021fbf50 = 1;
}

void func_020ed144(unsigned short value, int index)
{
    data_021fbff8[index].value = value;
    data_021fbff8[index].flag = 0;
}
