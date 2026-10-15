/* func_0208edb8 @ 0x0208edb8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208ecd0(void);
extern void func_0208a1f0(void *, void *);
extern void func_0208a1ec(void *, int);
extern void *func_0208a144(void *);
extern int data_020d5b4c;

void func_0208edb8(void *arg)
{
    int result = func_0208ecd0();
    if (result) {
        *(int *) ((char *) arg + 0x20) = 1;
        func_0208a1f0((char *) arg + 0xC, &data_020d5b4c);
        func_0208a1ec((char *) arg + 0xC, 1);
        func_0208a144((char *) arg + 0xC);
    }
}
