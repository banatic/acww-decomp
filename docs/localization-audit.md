# Auditing localized resource compatibility

```sh
python tools/audit_localization.py --european path/to/european.nds --language es
```

This tool contains no game resources. It needs both private dumps locally, checks their
supported SHA-1 values, and writes `build/localized-clean/audit-es.json`. The report contains filenames,
encodings, entry counts, classifications and reachability evidence, not game text or graphics.
All 1,791 script paths are inspected; unsupported files are not silently called translations.

The Spanish audit found:

| Classification | Files | Meaning |
|---|---:|---|
| Importable with the existing count/encoding checks | 1,657 | No new index mapping required by the container |
| Importable after removing empty string tail entries | 2 | All kept indices retain their numbers |
| Message-index mapping required | 41 | No automatic truncation or guessed branch renumbering |
| Shared legacy archives | 90 | Korean encoding 3; byte-identical contents in ENG/FRN/GER/SPN/ITA |
| Documented unreachable test actor | 1 | Evidence in the existing scene plan for the Korean retail spawner |

The previous 134-file fallback set therefore has two safely importable archives, 41 real
message-count differences, 90 shared legacy resources, and the one test archive. The remaining
fallback count is 132. Identical content in five languages is evidence of a shared resource,
not proof that a retail code path can never read it. The report marks those ninety archives'
runtime use as not established rather than guessing they are all dead code.

The one reachability claim is narrow and documented: `message/sp/npc/test_.bmg` belongs to
`npc_plc`, profile `0x7c` (`data_020e82f8`). The existing
[`scene-plan-groups.txt`](scene-plan-groups.txt) records that this profile is absent from the
retail spawner table (`data_020e1d8c`) and no game code constructs it. The claim concerns that
Korean retail spawner; manually driven calls are different. Other files are not assigned that
classification merely because their name or encoding looks old.

The two new imports are `string/st_password.bmg` (Korean 64 entries, European 66) and
`string/st_sweet.bmg` (36 and 37). The additional European entries contain only zero bytes.
The converter accepts this exception only for offset-only string archives, with more donor
entries and an entirely empty additional tail. It rebuilds INF1 using the original Korean
count, keeping every retained index unchanged. It never removes a nonempty row, truncates a
dialogue archive with attributes, fills a missing donor row, or shifts an existing index.

Six synthetic tests cover these boundaries and verify that a shared legacy archive is not
reported unreachable. As with the initial converter, matching entry counts alone do not prove
the semantic ordering of regional dialogue, and static classification is not gameplay coverage.
