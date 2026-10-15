/* func_02038cb4 @ 0x02038cb4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8c38(void *);

extern unsigned char data_020da560[];

void *func_02038cb4(void *p)
{
    *(void **) p = (void *) data_020da560;
    func_020a8c38(p);
    return p;
}
