/* func_020989b4 @ 0x020989b4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209985c(int);

struct Entry {
    char data[0xa04];
};

extern struct Entry data_021ef8ec[4];

void *func_020989b4(int object)
{
    int idx = func_0209985c(object);
    if (idx >= 0 && idx < 4) {
        return &data_021ef8ec[idx];
    }
    return 0;
}
