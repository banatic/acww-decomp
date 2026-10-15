/* func_ov004_0221bea4 @ 0x0221bea4, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203f130(void *);
extern void *func_02066a30(void *);
extern void *func_020b7f70(void *);
extern char data_ov004_022533e0[];
extern char data_ov004_02253454[];

void *func_ov004_0221bea4(void *this)
{
    func_0203f130(this);
    func_02066a30((char *) this + 0xec);
    *(void **) this = (void *) data_ov004_022533e0;
    *(void **) ((char *) this + 0xec) = (void *) data_ov004_02253454;
    func_020b7f70((char *) this + 0x138);
    return this;
}
