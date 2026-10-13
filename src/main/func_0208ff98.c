/* func_0208ff98 @ 0x0208ff98, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208ff98 {
    char pad_00[0xc];
    int unk_0C;
};

extern struct UnkStruct_0208ff98 data_021d369c;

int func_0208ff98(void)
{
    if (data_021d369c.unk_0C != 2) {
        return 0;
    }
    return 1;
}
