/* func_ov047_02261958 @ 0x02261958, 0x20 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov047_02262c14;
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);

void *func_ov047_02261958(void *p)
{
    *(void **) p = (void *) &data_ov047_02262c14;
    func_0202eb20(p);
    func_020edb3c(p);
    return p;
}
