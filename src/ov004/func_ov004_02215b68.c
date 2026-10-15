/* func_ov004_02215b68 @ 0x02215b68, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02215f40(void *);
extern char data_ov004_02250f88;
extern char data_ov004_02251034;

void *func_ov004_02215b68(void *this)
{
    func_ov004_02215f40(this);
    *(void **) this = &data_ov004_02250f88;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251034;
    return this;
}
