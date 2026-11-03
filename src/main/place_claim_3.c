/* place_claim_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205340c @ 0x0205340c, 0x1c bytes, Thumb
 * func_020533ac @ 0x020533ac, 0x60 bytes, Thumb
 */

typedef struct {
    unsigned char flag;
    unsigned char pad_01[3];
    char data[12];
    unsigned char type;
    unsigned char pad_11[3];
} UnkStruct_020533ac;

extern int func_02053448(char *address);
extern long long func_01ffd028(const void *ptr, int param);

int func_0205340c(char *base, int index)
{
    if (index < 4) {
        int offset = index * 20;
        return func_02053448(base + offset);
    }
    return 0;
}

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
