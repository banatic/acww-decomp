/* func_ov092_02298f20 @ 0x02298f20, 0x18 bytes, Thumb, module ov092
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov092_02299508;
extern void *func_ov002_0220826c(void *);

void *func_ov092_02298f20(void *this_ptr)
{
    *(void **) this_ptr = (void *) &data_ov092_02299508;
    func_ov002_0220826c(this_ptr);
    return this_ptr;
}
