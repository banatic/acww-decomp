/* func_020b97e4 @ 0x020b97e4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef char *FormatArguments;

extern void func_020b9808(short *, int, const signed char *);
extern int OS_VSNPrintf(char *, unsigned int, const char *, FormatArguments);

void func_020b97e4(short *arg0, int arg1, const char *format, FormatArguments args)
{
    char local_84[0x81];

    OS_VSNPrintf(local_84, 0x81, format, args);
    func_020b9808(arg0, arg1, (const signed char *) local_84);
}
