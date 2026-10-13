/* func_020a7360 @ 0x020a7360, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[8];
} Entry;
extern Entry data_021f435c[];
extern void func_020a7794(void *ptr, int a, int b, int c, int d);

void func_020a7360(int index, int a, int b, int c, int d)
{
    func_020a7794(&data_021f435c[index], a, b, c, d);
}
