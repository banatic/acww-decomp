/* func_ov003_0221c668 @ 0x0221c668, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov003_0221c490(void *p);
extern void *func_ov009_0226539c(void *p);

extern unsigned char data_ov003_02238934[];
extern unsigned char data_ov003_022389f8[];

void *func_ov003_0221c668(void *obj)
{
    unsigned int *p;

    *(unsigned int *) obj = (unsigned int) data_ov003_02238934;
    p = (unsigned int *) obj;
    p = (unsigned int *) ((char *) p + 0xec);
    *p = (unsigned int) data_ov003_022389f8;
    func_ov003_0221c490((char *) obj + 0x2b4);
    func_ov009_0226539c(obj);
    return obj;
}
