/* func_020ac358 @ 0x020ac358, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    unsigned short arr[5];
    unsigned char flag;
} Func020ac358Data;

void func_020ac358(Func020ac358Data *data, int index, unsigned short value)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (i == index) {
            data->arr[i] = value;
        } else {
            data->arr[i] = 0;
        }
    }
    data->flag = 1;
}
