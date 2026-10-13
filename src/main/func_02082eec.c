/* func_02082eec @ 0x02082eec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083100(void *p);
extern char data_020e1a54;

void *func_02082eec(void *param)
{
    func_02083100(param);
    *(void **) param = &data_020e1a54;
    return param;
}
