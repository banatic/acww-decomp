/* func_020770c0 @ 0x020770c0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_020736bc(void *, void *, void *);
extern int func_02052b90(void *);

int func_020770c0(void *param)
{
    void *local;
    func_020736bc(data_020ccf94, &local, param);
    return func_02052b90(&local);
}
