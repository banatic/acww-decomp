/* func_ov068_02275278 @ 0x02275278, 0x34 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202de4c(void *);
extern void *func_0202e5e0(void *);
extern void func_020edf54(void *);

extern unsigned char data_ov068_022780b0[];
extern unsigned char data_ov068_02278140[];

void *func_ov068_02275278(void *this)
{
    ((int *) this)[0] = (int) (unsigned int) data_ov068_02278140;
    *((int *) ((char *) this + 0x89c)) = (int) (unsigned int) data_ov068_022780b0;
    func_0202de4c((char *) this + 0x89c);
    func_0202e5e0(this);
    func_020edf54(this);
    return this;
}
