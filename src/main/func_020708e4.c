/* func_020708e4 @ 0x020708e4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020707d0(void *);
extern void func_020a8874(void *, void *, void *);
extern void func_020a8a70(void *, void *, int, int);
extern void func_020707b8(void *);

void func_020708e4(void *param1, void *param2, void *param3)
{
    char buffer[0x60];
    func_020707d0(buffer);
    func_020a8874(buffer, param2, param3);
    func_020a8a70(param1, buffer, 0, 0);
    func_020707b8(buffer);
}
