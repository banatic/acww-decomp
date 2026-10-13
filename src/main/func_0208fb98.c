/* func_0208fb98 @ 0x0208fb98, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208fb54(void *param1);
extern void func_02001cf4(int param1);
extern void func_02001bb4(int param1);

void func_0208fb98(void *param1)
{
    unsigned char temp;

    *(int *) ((char *) param1 + 0xc) = 1;
    func_0208fb54(param1);
    temp = *(unsigned char *) ((char *) param1 + 0x12);
    if (temp != 0) {
        func_02001cf4(0x10);
        func_02001bb4(4);
    }
}
