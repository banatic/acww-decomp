/* func_ov082_02279064 @ 0x02279064, 0x18 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *);
extern unsigned char data_ov082_0227978c[];

void *func_ov082_02279064(void *p)
{
    *(unsigned int *) p = (unsigned int) data_ov082_0227978c;
    func_0202eb20(p);
    return p;
}
