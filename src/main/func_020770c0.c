/* func_020770c0 @ 0x020770c0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_020736bc(void *, void *, void *);
extern void func_02052b90(void *);

void func_020770c0(void *param, int sequence, unsigned char category, unsigned int player)
{
    void *local;
    func_020736bc(data_020ccf94, &local, param);
    func_02052b90(&local);
}
