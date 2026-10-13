/* func_02023348 @ 0x02023348, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void *);
extern int func_02099640(int);
extern void func_0206f80c(void *);
extern int func_0208150c(int);
extern void func_0209ae70(void *, int, void *);
extern int func_0207f270(int);
extern int func_020794d0(int);
extern void func_0209bd5c(int);
extern void func_0207b57c(void *);

extern unsigned char data_021e5a2c[];

void func_02023348(void *param)
{
    void *p4;
    int local[2];
    int r1;

    p4 = (void *) func_02099640(func_020984e8(param));
    local[0] = 0;
    local[1] = 0;
    func_0206f80c(local);
    r1 = func_0208150c(*(int *) (*(char **) ((char *) param + 0x100) + 0x830));
    p4 = (char *) p4 + 0xa4;
    func_0209ae70(p4, r1, local);
    func_0209bd5c(func_020794d0(func_0207f270(*(int *) (*(char **) ((char *) param + 0x100) + 0x830))));
    func_0207b57c((void *) data_021e5a2c);
}
