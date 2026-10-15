/* func_0207626c @ 0x0207626c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073424(void *);
extern void func_020736bc(void *, int, void *);
extern void func_02073404(void *, void *);
extern void func_020a6db0(void);

void func_0207626c(void *param, int sequence, unsigned char category, unsigned int player)
{
    void *ptr = data_020ccf94;
    int ret = func_02073424(ptr);
    func_020736bc(ptr, ret, param);
    func_02073404(ptr, param);
    func_020a6db0();
}
