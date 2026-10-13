/* func_02084890 @ 0x02084890, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073dd4(void *p, int arg);
extern int func_0208602c(void);
extern int func_02086108(int a, int b);
extern int func_02084ad0(void);
extern int func_02084af0(void);

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02084890;

extern UnkStruct_02084890 *data_020ccf94;

int func_02084890(void)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0 && func_02086108(func_0208602c(), 8) != 0 &&
        func_02084ad0() == 0 && func_02084af0() == 0) {
        return 1;
    } else {
        return 0;
    }
}
