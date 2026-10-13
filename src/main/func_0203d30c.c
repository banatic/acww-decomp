/* func_0203d30c @ 0x0203d30c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
} Flags;

int func_0203d30c(Flags *p)
{
    if (p->b1) {
        return 1;
    } else {
        return 0;
    }
}
