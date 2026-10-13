/* func_02057060 @ 0x02057060, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *obj, void *data);

extern unsigned char data_020dd184[];

void *func_02057060(void *obj)
{
    *(void **) obj = (void *) data_020dd184;
    func_020edb3c(obj, (void *) data_020dd184);
    return obj;
}
