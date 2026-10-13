/* ciSetQuietModeEnumJoinedChannelsA @ 0x020f7d04, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void ciAddUNQUIETFilter(int, int);

void ciSetQuietModeEnumJoinedChannelsA(int a, int b, int c)
{
    ciAddUNQUIETFilter(a, c);
}
