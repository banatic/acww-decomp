/* func_0204fd6c @ 0x0204fd6c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0204fd6c UnkStruct_0204fd6c;
extern int data_020dcd78;
extern unsigned char *data_021c8184;
extern int func_02056f28(unsigned char *p, UnkStruct_0204fd6c *q);
int func_0204fd6c(int i, UnkStruct_0204fd6c *q)
{
    int r = 0;
    if (i >= 0 && i < data_020dcd78) {
        unsigned char *e = data_021c8184 + 0x50 + i * 0x16c;
        int k = *(int *) (e + 0x40);
        if (k < 0 || k >= 0x38) {
            return 0;
        }
        if (func_02056f28(e + 0x134, q) != 0) {
            r = 1;
        }
    }
    return r;
}
