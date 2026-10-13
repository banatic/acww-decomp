/* func_020bec70 @ 0x020bec70, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Entry {
    signed char pad_00[12];
    signed char unk_0C;
    signed char unk_0D;
    signed char pad_0E[2];
} data_020d2bac[];

int func_020bec70(signed char *arg0, int arg1)
{
    struct Entry *entry = &data_020d2bac[arg1];
    signed char d = entry->unk_0D;
    signed char c = entry->unk_0C;
    int result = 1;
    if (d >= 0 && c >= 0) {
        if (c != (arg0 + (d - 12))[4]) {
            result = 0;
        }
    }
    return result;
}
