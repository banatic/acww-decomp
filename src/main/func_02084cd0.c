/* func_02084cd0 @ 0x02084cd0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02084af0(int a, int b, int c);
extern int func_02073dd4(void *ptr, int val);
extern int func_02084d08(int a, int b, int c, int d);

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02084cd0;

extern UnkStruct_02084cd0 *data_020ccf94;

int func_02084cd0(int a, int b, int c)
{
    if (func_02084af0(a, b, c) == 0) {
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
            return func_02084d08(a, 1, b, c);
        }
    }
    return 0;
}
