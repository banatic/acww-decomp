/* func_02082d90 @ 0x02082d90, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083100(void *);
extern char data_020e19dc;

void *func_02082d90(void *p)
{
    func_02083100(p);
    *(void **) p = (void *) &data_020e19dc;
    return p;
}
