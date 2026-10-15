/* func_ov085_02278efc @ 0x02278efc, 0x18 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *);
extern char data_ov085_0227945c[];

void *func_ov085_02278efc(void *param)
{
    *(void **) param = (void *) data_ov085_0227945c;
    func_0202eb20(param);
    return param;
}
