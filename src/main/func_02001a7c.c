/* func_02001a7c @ 0x02001a7c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001a48(void);
extern void func_02001d00(int);
extern void func_02001ce8(int);
extern void func_02001b7c(int);
extern unsigned char data_0213fe94[];

void func_02001a7c(void)
{
    unsigned char *p;
    unsigned char val;

    func_02001a48();
    func_02001d00(0x1f);
    func_02001ce8(0x10);
    func_02001b7c(4);
    p = data_0213fe94;
    val = p[0x12];
    val |= 1;
    p[0x12] = val;
}
