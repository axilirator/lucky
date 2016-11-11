/*
 * Knowledge-based password generator
 * Case mixer block
 * 
 * (C) 2016 by Vadim Yanitskiy <axilirator@gmail.com>
 *
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <stdio.h>
#include <string.h>
#include <talloc.h>

#include <lucky/core.h>
#include <lucky/blocks.h>

static int char_up(char *str, int idx)
{
	int rc = 0;

	if (str[idx] >= 'a' && str[idx] <= 'z') {
		str[idx] -= 32;
		rc++;
	}

	return rc;
}

static int char_down(char *str, int idx)
{
	int rc = 0;

	if (str[idx] >= 'A' && str[idx] <= 'Z') {
		str[idx] += 32;
		rc++;
	}

	return rc;
}

static void str_down(char *str, int len)
{
	int i;

	for (i = 0; i < len; i++)
		char_down(str, i);
}

static void handle(char *input)
{
	static int counter = 0;
	printf("#%d %s\n", ++counter, input);
}

static void mix_case(char *buffer, int len, int skip, int level)
{
	int i, rc;

	if (level == 1) {
		for (i = skip; i < len; i++) {
			rc = char_up(buffer, i);
			if (!rc)
				continue;

			handle(buffer);
			char_down(buffer, i);
		}
	} else {
		for (i = skip; i < len; i++) {
			rc = char_up(buffer, i);
			if (!rc)
				continue;

			mix_case(buffer, len, i + 1, level - 1);
			char_down(buffer, i);
		}
	}
}

static int input_handler(char **words, int count)
{
	char *buffer = talloc(NULL, char);
	int i, len;
	int level;

	for (i = 0; i < count; i++) {
		// Determine length
		len = strlen(words[i]);

		// Duplicate the source string
		talloc_realloc(NULL, buffer, char, len + 1);
		strcpy(buffer, words[i]);

		// We need a single case
		str_down(buffer, len);

		// Lower case variation
		handle(buffer);

		// Other possible case mixes
		for (level = 1; level <= len; level++)
			mix_case(buffer, len, 0, level);
	}

	talloc_free(buffer);
	return 0;
}

struct block_def ulcase = {
	.name = "ulcase",
	.description = "Upper / Lower case mixer",

	.category = BLOCK_PROCESSOR,
	.input_handler = &input_handler,
};
