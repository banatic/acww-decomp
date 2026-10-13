/* func_0207f29c @ 0x0207f29c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int param);
extern int func_0207cf14(void *ptr, int value);
extern char data_021e5a2c;

int func_0207f29c(int param)
{
    void *p = (void *) &data_021e5a2c;
    int result = -1;
    if (p != 0) {
        int tmp = func_0208150c(param);
        result = func_0207cf14(p, tmp);
    }
    return result;
}
