/* func_020a7258 @ 0x020a7258, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a72d0(void);

typedef struct {
    char pad_00[0x64];
    int unk_64;
} Struct020ccf94;

extern Struct020ccf94 *data_020ccf94;

int func_020a7258(void)
{
    if (data_020ccf94->unk_64 < 4) {
        return func_020a72d0();
    } else {
        return 1;
    }
}
