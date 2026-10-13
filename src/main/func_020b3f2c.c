/* func_020b3f2c @ 0x020b3f2c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    char type;
    char pad_01[3];
};
int func_020b3f2c(struct Entry *p)
{
    int count = 0;
    while (p->type == 'R' || p->type == 'M') {
        p++;
        count++;
    }
    return count;
}
