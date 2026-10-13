/* func_ov142_02299ae0 @ 0x02299ae0, 0x28 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e930(void *);
extern void func_ov002_0220a580(void *);

int func_ov142_02299ae0(void *self)
{
    if (func_0208e930((char *) self + 0x14c)) {
        func_ov002_0220a580((char *) self + 0x14c);
        return 1;
    }
    return 0;
}
