/* func_02013894 @ 0x02013894, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Func02013894Data {
    unsigned char pad_00[8];
    unsigned int value;
};

int func_02013894(const struct Func02013894Data *data)
{
    if (data->value < 7) {
        return 1;
    }
    return 0;
}
