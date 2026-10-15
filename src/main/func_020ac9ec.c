/* func_020ac9ec @ 0x020ac9ec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208e7f0(void *obj);
extern char data_020e4030;

void *func_020ac9ec(void *obj)
{
    *(void **) obj = &data_020e4030;
    func_0208e7f0(obj);
    return obj;
}
