/* func_020386c4 @ 0x020386c4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned long long data[6];
} Data48;

extern Data48 data_021fbe48;
extern void func_020e96c8(Data48 *, int, int, int, int, int, int);

void func_020386c4(unsigned char *self)
{
    func_020e96c8(&data_021fbe48, 0, 0, 0xfffff000, 0, 0, 0xfffff000);
    {
        Data48 *dst = (Data48 *) (self + 0x68);
        *dst = data_021fbe48;
    }
}
