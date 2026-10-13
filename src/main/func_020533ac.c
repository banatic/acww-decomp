/* func_020533ac @ 0x020533ac, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern long long func_01ffd028(const void *ptr, int param);

typedef struct {
    unsigned char flag;
    unsigned char pad_01[3];
    char data[12];
    unsigned char type;
    unsigned char pad_11[3];
} UnkStruct_020533ac;

int func_020533ac(UnkStruct_020533ac *arr, int n, unsigned char type, int param)
{
    if (n < 4) {
        unsigned int i;
        for (i = 0; i < 4; i++) {
            UnkStruct_020533ac *e = &arr[i];
            if (i == n) {
                continue;
            }
            if (e->flag == 0) {
                continue;
            }
            if (type != e->type) {
                continue;
            }
            if (func_01ffd028(e->data, param) < 0x2400) {
                return 0;
            }
        }
        return 1;
    } else {
        return 0;
    }
}
