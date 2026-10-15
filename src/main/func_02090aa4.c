/* func_02090aa4 @ 0x02090aa4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021d52c4;
extern void func_020907c4(void *, int, void (*callback)(void *));

void func_02090aa4(int index, void (*callback)(void *))
{
    func_020907c4((char *) data_021d52c4 + 0x35c, index, callback);
}
