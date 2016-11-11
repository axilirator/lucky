/*
 * Knowledge-based password generator
 * File source block
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

static FILE *fp;

static int file_open(const char *name)
{
	int rc = 0;

	fp = fopen(name, "r");
	if (!fp)
		rc = -1;

	return rc;
}

static void file_close(void)
{
	if (fp != NULL)
		fclose(fp);
}

static void handle(char *input)
{
	static int counter = 0;
	printf("#%d %s", ++counter, input);
}

static void file_read(void)
{
	char *buffer = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = getline(&buffer, &len, fp)) != -1)
		handle(buffer);

	if (buffer)
		free(buffer);
}

void input(const char *name)
{
	file_open(name);
	file_read();
	file_close();
}
