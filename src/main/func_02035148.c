/* func_02035148 @ 0x02035148, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x13];
    unsigned char flag;
    unsigned char pad_14[0x08];
} Entry;

typedef struct {
    Entry array[16];
    int count;
} Container;

extern int func_02034ee4(Container *param, unsigned short);

void func_02035148(Container *param, unsigned short argument1)
{
    int ret = func_02034ee4(param, (unsigned short) argument1);
    if (ret >= 0 && ret < param->count) {
        param->array[ret].flag = 1;
    }
}
