/* func_0201596c @ 0x0201596c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201596c {
    char unk_00[0x64];
    unsigned int unk_64;
    char unk_68[0x44];
    unsigned char unk_AC;
    unsigned char unk_AD;
};

extern int func_0201595c(struct UnkStruct_0201596c *ptr);

int func_0201596c(struct UnkStruct_0201596c *ptr, unsigned int value)
{
    int ret = 0;
    if (ptr->unk_64 == 0xc || func_0201595c(ptr) == 0) {
        ptr->unk_64 = value;
        ptr->unk_AC = 0;
        ptr->unk_AD = 1;
        ret = 1;
    }
    return ret;
}
