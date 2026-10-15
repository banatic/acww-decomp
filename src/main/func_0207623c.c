/* func_0207623c @ 0x0207623c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void *func_020733c4(void *);
extern void func_020736bc(void *, void *, void *);
extern void func_020733a0(void *, void *);

void func_0207623c(void *param, int sequence, unsigned char category, unsigned int player)
{
    void *p = data_020ccf94;
    void *res;

    res = func_020733c4(p);
    func_020736bc(p, res, param);
    func_020733a0(p, param);
}
