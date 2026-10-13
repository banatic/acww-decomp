/* func_0206abbc @ 0x0206abbc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a861c(void *param1, void *param2);

void func_0206abbc(void *param0)
{
    unsigned short temp;
    void *sp;
    void *r4 = param0;

    func_020a861c((void *) ((unsigned int) param0 + 0x38), &sp);
    temp = *(unsigned short *) &sp;
    *(unsigned int *) ((unsigned int) r4 + 0x58) = (unsigned int) temp << 12;
    *(unsigned char *) (*(unsigned int *) ((unsigned int) r4 + 0x24) + 0x1a4a) = 1;
}
