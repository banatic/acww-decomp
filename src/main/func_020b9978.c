/* func_020b9978 @ 0x020b9978, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021f6ca0[];
extern void func_02065c2c(void *a, void *b);

void func_020b9978(void *p)
{
    void *q;
    q = p;
    if (q) {
        q = (char *) q + 4;
    }
    func_02065c2c(data_021f6ca0, q);
}
