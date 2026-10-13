/* func_020bee4c @ 0x020bee4c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020beca4(void *obj, int arg);

extern unsigned char data_021fba00[];

void func_020bee4c(unsigned char *self, int arg)
{
    self[9] = 1;
    func_020beca4((void *) data_021fba00, arg);
}
