/* func_02052e3c @ 0x02052e3c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bc64(int);
extern int func_02053be0(int);
extern int func_0204bc7c(int);

int *func_02052e3c(int *out, int in)
{
    int temp;
    *out = -1;
    temp = func_0204bc64(in);
    if (temp != -1) {
        *out = func_02053be0(temp);
        *(out + 1) = func_0204bc7c(in);
    }
    return out;
}
