/* func_ov134_02299a60 @ 0x02299a60, 0x22 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e930(void *);
extern void func_ov002_0220a580(void *);

int func_ov134_02299a60(void *param)
{
    if (func_0208e930((char *) param + 0x18)) {
        func_ov002_0220a580((char *) param + 0x18);
        return 1;
    }
    return 0;
}
