/* func_02090ed4 @ 0x02090ed4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204cab4(void *obj);
extern short *data_020e2488[];

short func_02090ed4(void *obj)
{
    int idx;
    unsigned char b;
    idx = func_0204cab4(obj);
    b = ((unsigned char *) obj)[0x80];
    return data_020e2488[b][idx];
}
