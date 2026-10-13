/* func_020826e0 @ 0x020826e0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Entry {
    int value;
    int pad_04;
} Entry;

typedef struct UnkStruct_020826e0 {
    char pad_00[0x40];
    Entry entries[4];
} UnkStruct_020826e0;

extern int func_020828c0(UnkStruct_020826e0 *base, Entry *entry);

int func_020826e0(UnkStruct_020826e0 *base, int index)
{
    int result = 0;

    if (index >= 0 && index < 4) {
        Entry *p = &base->entries[index];
        if (func_020828c0(base, p)) {
            result = p->value;
        }
    }

    return result;
}
