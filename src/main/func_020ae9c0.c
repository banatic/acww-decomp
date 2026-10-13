/* func_020ae9c0 @ 0x020ae9c0, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern void func_0209e140(void *, int);
extern int func_02073d90(int);
extern int func_020ae92c(void *, void *);
extern void func_020ae96c(void *, int, int, int);
extern void func_020ae900(void *, void *);
extern int data_020ccf94;

void func_020ae9c0(void *param)
{
    unsigned int local[2];

    local[0] = 0;
    local[1] = 0;

    func_0209e474(local);
    if (((unsigned char *) local)[2] < 6) {
        func_0209e140(local, 1);
    }
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    if (func_020ae92c(param, local) == 0) {
        return;
    }
    func_020ae96c(param, ((unsigned char *) local)[5], ((unsigned char *) local)[4], ((unsigned char *) local)[3]);
    func_020ae900(param, local);
}
