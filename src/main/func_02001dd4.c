/* func_02001dd4 @ 0x02001dd4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x11];
    unsigned char flag;
} Reg1;
typedef struct {
    char pad_00[0x68];
    int param1;
    int param2;
} Reg2;

extern volatile Reg1 data_0213fe74;
extern volatile Reg2 data_0213fdf4;

void func_02001dd4(int arg0, int arg1)
{
    data_0213fe74.flag |= 0x40;
    data_0213fdf4.param1 = arg0;
    data_0213fdf4.param2 = arg1;
}
