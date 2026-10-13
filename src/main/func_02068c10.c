/* func_02068c10 @ 0x02068c10, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208fdb8(void *ptr);

void func_02068c10(void *arg)
{
    void *r4 = arg;
    func_0208fdb8((char *) r4 + 0x50);
    *(unsigned int *) ((char *) r4 + 0x7c) = 4;
}
