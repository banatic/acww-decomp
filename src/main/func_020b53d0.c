/* func_020b53d0 @ 0x020b53d0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __thumb void func_020a941c(void *);
extern __arm void func_020edb3c(void *);

extern unsigned char data_020e3e68[];
extern unsigned char data_020e5278[];

void *volatile *func_020b53d0(void *volatile *this)
{
    *this = (void *) data_020e5278;
    *this = (void *) data_020e3e68;
    func_020a941c((void *) this);
    func_020edb3c((void *) this);
    return this;
}
