/* func_0208bcfc @ 0x0208bcfc, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208c610(void *ptr);
extern void func_0208bccc(void *ptr);

void func_0208bcfc(void *ptr)
{
    void *r4 = ptr;
    if (func_0208c610((char *) ptr + 0x28) != 0) {
        func_0208bccc(r4);
    }
}
