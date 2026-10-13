/* func_ov003_0221fd60 @ 0x0221fd60, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee660(void *obj);
extern void func_ov003_0221f618(void *obj);
extern void func_ov003_0221f204(void *obj);
extern void func_020576cc(void *obj);
extern void func_ov003_0221ef7c(void *obj);

extern unsigned char data_020da13c[];
extern unsigned char data_ov003_02239a58[];

void *func_ov003_0221fd60(void *self)
{
    func_020ee660(self);
    *(int *) self = (unsigned int) data_020da13c;
    *(int *) self = (unsigned int) data_ov003_02239a58;
    func_ov003_0221f618((char *) self + 0x54);
    func_ov003_0221f204((char *) self + 0x150);
    func_020576cc((char *) self + 0x1f0);
    func_020576cc((char *) self + 0x280);
    func_ov003_0221ef7c((char *) self + 0x310);
    return self;
}
