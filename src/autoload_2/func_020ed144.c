/* func_020ed144 @ 0x020ed144, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short value;
    unsigned char flag;
} Unk_020ed144;

extern Unk_020ed144 data_021fbff8[];

void func_020ed144(unsigned short value, int index)
{
    data_021fbff8[index].value = value;
    data_021fbff8[index].flag = 0;
}
