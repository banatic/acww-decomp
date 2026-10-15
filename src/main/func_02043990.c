/* func_02043990 @ 0x02043990, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int lo;
    unsigned int hi;
} U64;

extern int func_02044858(unsigned int a);
extern int func_020439b4(int x, U64 *ptr, unsigned int c);

int func_02043990(unsigned int a, U64 *b, unsigned int c)
{
    int r;
    U64 local;
    r = func_02044858(a);
    local.lo = b->lo;
    local.hi = b->hi;
    return func_020439b4(r, &local, c);
}
