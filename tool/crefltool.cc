/*
 * crefltool - tool to dump crefl reflection metadata.
 *
 * Copyright (c) 2020 Michael Clark <michaeljclark@mac.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "cmodel.h"
#include "cdump.h"
#include "cfileio.h"

int main(int argc, const char **argv)
{
    decl_db *db;

    if (argc != 3) goto help_exit;

    enum { _dump, _dump_all, _dump_ext, _stats } mode;

    if (strcmp(argv[1], "--dump") == 0) mode = _dump;
    else if (strcmp(argv[1], "--dump-all") == 0) mode = _dump_all;
    else if (strcmp(argv[1], "--dump-ext") == 0) mode = _dump_ext;
    else if (strcmp(argv[1], "--stats") == 0) mode = _stats;
    else goto help_exit;

    db = crefl_db_new();
    crefl_db_read_file(db, argv[2]);
    switch (mode) {
        case _dump_ext: crefl_db_set_dump_fmt(crefl_db_dump_ext); goto dump;
        case _dump_all: crefl_db_set_dump_fmt(crefl_db_dump_all); goto dump;
        case _dump: dump: crefl_db_dump(db); break;
        case _stats: crefl_db_dump_stats(db); break;
    }
    crefl_db_destroy(db);
    exit(0);

help_exit:
    fprintf(stderr, "usage: %s <command> <filename.refl>\n\n"
    "Commands:\n\n"
    "--dump      dump main reflection database fields in 80-col format\n"
    "--dump-all  dump all reflection database fields in 160-col format\n"
    "--dump-ext  dump all reflection database fields in 192-col format\n"
    "--stats     print reflection database statistics\n\n", argv[0]);
    exit(1);
}
