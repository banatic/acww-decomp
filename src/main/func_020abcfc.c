/* func_020abcfc @ 0x020abcfc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aca70(void *);

int func_020abcfc(void *arg0)
{
    int result;
    int offset;
    void *ptr;

    ptr = arg0;
    result = func_020aca70((char *) ptr + 0xe4);
    offset = *(short *) ((char *) ptr + 0x1a);
    return result + 0x60 - offset;
}
