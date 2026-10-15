/* func_0209fea4 @ 0x0209fea4, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209f150(void *, int);
extern unsigned char *strcpy(void *, void *);
extern char *func_0212d914(void *, void *);
extern void func_02073100(void);
extern int func_020eb108(void *, const void *, unsigned int, unsigned int);

extern void *data_020e3808;
extern void *data_020e380c;
extern unsigned int data_020e3800;

extern unsigned char data_021dc7a8[];
extern unsigned char data_021f3d90[];

int func_0209fea4(void)
{
    char buffer[128];
    unsigned int val;

    if (func_0209f150((void *) data_021dc7a8, 0x14)) {
        return 0;
    }

    strcpy(buffer, data_020e3808);
    func_0212d914(buffer, data_020e380c);
    val = data_020e3800;
    func_02073100();

    return func_020eb108(buffer, (void *) data_021f3d90, 0x114, val) ? 1 : 0;
}
