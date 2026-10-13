/* func_02079260 @ 0x02079260, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    unsigned char unk_00[0x1d];
    unsigned char flags;
    unsigned char unk_1E[14];
};

extern struct Entry *func_02079350(void);

void func_02079260(void)
{
    struct Entry *p;
    int i;

    p = func_02079350();
    for (i = 0; i < 8; i++) {
        p->flags &= ~4;
        p++;
    }
}
