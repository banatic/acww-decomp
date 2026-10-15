/* func_0202e4c8 @ 0x0202e4c8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int object);
extern int func_02003648(unsigned char *);

int func_0202e4c8(void *param)
{
    unsigned int object;

    if (((*(unsigned short *) ((char *) param + 0xEA) & 0xF000) >> 12) == 0xE) {
        if ((object = *(unsigned int *) ((char *) param + 0x830)) != 0) {
            return func_02003648((unsigned char *) func_0208150c(object));
        }
    }
    return 0xFFFF;
}
