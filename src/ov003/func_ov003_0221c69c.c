/* func_ov003_0221c69c @ 0x0221c69c, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov009_0226552c(void *p);
extern void *func_ov003_0221c4a4(void *p);

extern unsigned char data_ov003_02238934[];
extern unsigned char data_ov003_022389f8[];

void *func_ov003_0221c69c(void *obj)
{
    func_ov009_0226552c(obj);
    *(unsigned int *) obj = (unsigned int) data_ov003_02238934;
    *(unsigned int *) ((char *) obj + 0xEC) = (unsigned int) data_ov003_022389f8;
    func_ov003_0221c4a4((char *) obj + 0x2B4);
    return obj;
}
