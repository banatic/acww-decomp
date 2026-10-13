/* func_020830dc @ 0x020830dc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *object, unsigned int value);

extern unsigned char data_020e1a2c[];

void *func_020830dc(void *object)
{
    *((unsigned int *) object) = (unsigned int) data_020e1a2c;
    func_020edb3c(object, (unsigned int) data_020e1a2c);
    return object;
}
