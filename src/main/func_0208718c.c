/* func_0208718c @ 0x0208718c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct BitFields {
    unsigned char value : 3;
    unsigned char rest : 5;
};

void func_0208718c(struct BitFields *p)
{
    p->value = p->value + 1;
}
