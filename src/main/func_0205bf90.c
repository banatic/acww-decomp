/* func_0205bf90 @ 0x0205bf90, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *p);
void func_0205bf90(unsigned char *out)
{
    int t[2];
    t[0] = 0;
    t[1] = 0;
    func_0209e474(t);
    out[0] = ((unsigned char *) t)[3];
    out[1] = ((unsigned char *) t)[4];
    out[2] = ((unsigned char *) t)[5];
    out[3] = 0;
}
