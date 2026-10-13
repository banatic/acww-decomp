/* func_0201cde8 @ 0x0201cde8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0201cde8;

extern UnkStruct_0201cde8 *data_020ccf94;
extern int func_02073dd4(UnkStruct_0201cde8 *ptr, int field);
extern unsigned char func_0207af30(void);

void func_0201cde8(char *arg)
{
    arg[0x640] = 0x0B;
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        arg[0x640] = func_0207af30();
    }
}
