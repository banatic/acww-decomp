/* func_ov003_0221d9c0 @ 0x0221d9c0, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226552c(void *p);
extern char data_ov003_02238f28;
extern char data_ov003_02238fec;
extern void func_02055210(void *p);
extern void func_020565c8(void *p);
extern unsigned int data_ov003_0223c928[8];

void *func_ov003_0221d9c0(void *param)
{
    unsigned int i;
    unsigned int v;
    func_ov009_0226552c(param);
    *(void **) param = &data_ov003_02238f28;
    *(void **) ((char *) param + 0xEC) = &data_ov003_02238fec;
    func_02055210((char *) param + 0x2B4);
    func_020565c8((char *) param + 0x36C);
    i = 0;
    v = i;
    for (; i < 8; i++) {
        data_ov003_0223c928[i] = v;
    }
    return param;
}
