/* func_02042954 @ 0x02042954, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02042954 {
    unsigned char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
} UnkStruct_02042954;

extern int func_02077f3c(int, char *, unsigned char, unsigned char, unsigned char);

int func_02042954(int unused, int limit, char *ptr, unsigned char *buf, int count, UnkStruct_02042954 *info)
{
    int i = 0;
    if (buf != 0) {
        int n = 0;
        while (n < count) {
            if (*buf == 0) {
                if (--limit < 0) {
                    break;
                }
            }
            buf++;
            i++;
            n++;
        }
        *buf = 1;
    }
    return func_02077f3c(i, ptr, info->unk_05, info->unk_04, info->unk_03);
}
