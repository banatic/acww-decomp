/* func_020ea990 @ 0x020ea990, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eacf8(long long);

struct UnkStruct_020ea990 {
    int x;
    int y;
    int z;
};

int func_020ea990(struct UnkStruct_020ea990 *a, struct UnkStruct_020ea990 *b)
{
    int d;
    long long s;

    d = a->x - b->x;
    s = (long long) d * d;
    d = a->z - b->z;
    s += (long long) d * d;

    return func_020eacf8(s);
}
