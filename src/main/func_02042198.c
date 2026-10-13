/* func_02042198 @ 0x02042198, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    char pad[12];
    int field;
} data_021c75b8;
extern int func_02001aac(int arg);

int func_02042198(void)
{
    return func_02001aac(data_021c75b8.field);
}
