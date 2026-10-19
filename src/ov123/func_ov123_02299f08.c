/* func_ov123_02299f08 @ 0x02299f08, 0x38 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(unsigned int);
extern void func_ov123_02299640(void *, unsigned int);

void func_ov123_02299f08(void *param)
{
    unsigned char tmp;
    unsigned char tmp2;
    void *p;

    func_0200467c(0x866);
    func_ov123_02299640(param, 0x100);

    p = (char *) param + 0xa8;
    tmp = *(unsigned char *) p;
    p = (char *) param + 0xad;
    *(unsigned char *) p = tmp;

    p = (char *) param + 0xa9;
    tmp2 = *(unsigned char *) p;
    p = (char *) param + 0xae;
    *(unsigned char *) p = tmp2;
}
