/* func_0209895c @ 0x0209895c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209985c(int);
extern int func_0209805c(const unsigned char *ptr);
extern unsigned char data_021ef8ec[];

int func_0209895c(int object)
{
    int idx;

    idx = func_0209985c(object);
    if (idx >= 0 && idx < 4) {
        return func_0209805c(data_021ef8ec + idx * 0x0a04);
    } else {
        return 0;
    }
}
