/* func_0205eac4 @ 0x0205eac4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x10];
    int unk_10;
} Entry;

typedef struct {
    char pad_00[0x9c];
    Entry entry;
} Record;

extern Record data_021ca16c;
extern Record *func_0205f130(Record *base, unsigned char index);

void func_0205eac4(unsigned char *key, int value)
{
    Entry *e;

    e = &func_0205f130(&data_021ca16c, *key)->entry;
    e->unk_10 = value;
}
