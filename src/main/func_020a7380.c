/* func_020a7380 @ 0x020a7380, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
} Entry;

extern Entry data_021f434c[];
extern void func_020a76e0(Entry *entry, int arg);

void func_020a7380(int index, int arg)
{
    func_020a76e0(&data_021f434c[index], arg);
}
