/* func_ov046_022612ec @ 0x022612ec, 0x18 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *arg0);

extern unsigned char data_ov046_0226204c[];

void *func_ov046_022612ec(void *p)
{
    *(void **) p = (void *) data_ov046_0226204c;
    func_0202eb20(p);
    return p;
}
