/* func_ov009_022631b4 @ 0x022631b4, 0x68 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x136];
    unsigned short unk_136;
} InputStruct;

extern char data_020d1f24[];
extern void func_020b2a68(char *dst, char *src);
extern int func_020b2a50(char *buf);
extern void func_020b2a64(char *buf);

int func_ov009_022631b4(InputStruct *input)
{
    int flag = 0;
    unsigned short val = input->unk_136;
    unsigned int idx;
    char *ptr;
    char local[16];
    int result;

    if (val >= 0x5000u && val <= 0x5021u) {
        flag = 1;
    }
    if (flag != 0) {
        idx = val & 0xFFF;
    } else {
        idx = -1;
    }
    if (idx < 0x22u) {
        ptr = data_020d1f24 + idx * 10;
    } else {
        ptr = data_020d1f24;
    }
    func_020b2a68(local, ptr);
    result = func_020b2a50(local);
    func_020b2a64(local);
    return result;
}
