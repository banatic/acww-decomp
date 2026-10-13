/* func_0204093c @ 0x0204093c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02040bcc(void *tbl, int a);
extern void *func_020409c8(void *tbl, int idx);
extern int func_020984d4(void);
extern char data_021f39c0[];

void func_0204093c(int a)
{
    void *table;
    int idx;
    unsigned char *p;

    table = data_021f39c0;
    idx = func_02040bcc(table, a);
    p = func_020409c8(table, idx);
    if (p != 0) {
        if (a == 0x44) {
            p[5] = 0xff;
        } else {
            int shift = func_020984d4();
            p[5] = (unsigned char) ((p[5] & ~(1 << shift)) | (1 << shift));
        }
    }
}
