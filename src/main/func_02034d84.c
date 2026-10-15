/* func_02034d84 @ 0x02034d84, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm void *func_020ee660(void *);
extern void *func_02035510(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020da334[];

void *func_02034d84(void *obj)
{
    func_020ee660(obj);
    *(void **) obj = (void *) data_020da13c;
    *(void **) obj = (void *) data_020da334;
    func_02035510((char *) obj + 0x50);
    return obj;
}
