/* func_020bb89c @ 0x020bb89c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020bbd30(void);
extern int func_020bbcfc(void *);
extern int func_020bbb20(void *);
extern void func_020bba14(void);
extern int *data_021f6cd8;

extern unsigned char data_021f8b14[];

int func_020bb89c(void *param)
{
    int ret = 0;
    if (func_020bbd30() != 0 && func_020bbcfc((void *) data_021f8b14) != 0) {
        if (data_021f6cd8 != 0) {
            ret = func_020bbb20(param);
        } else {
            func_020bba14();
            ret = 1;
        }
    }
    return ret;
}
