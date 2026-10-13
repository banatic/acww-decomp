/* func_02038b80 @ 0x02038b80, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064328(void *dest, const void *src, unsigned int size);
extern void func_02038bac(void *obj, const void *data);
extern unsigned int data_021c5938;
extern char data_020da590[];
extern char data_021c5970;

char *func_02038b80(void)
{
    char buf[20];
    func_02064328(buf, data_020da590, data_021c5938);
    func_02038bac(&data_021c5970, buf);
    return &data_021c5970;
}
