/*
 * Author: Paul.Russell@rustcorp.com.au and mneuling@radlogic.com.au
 *
 * Based on the ipchains code by Paul Russell and Michael Neuling
 *
 *	iptables -- IP firewall administration for kernels with
 *	firewall table (aimed for the 2.3 kernels)
 *
 *	See the accompanying manual page iptables(8) for information
 *	about proper usage of this program.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iptables.h>

int
main(int argc, char *argv[])
{
	int ret;
	char *table = "filter";
	iptc_handle_t *handle;

	handle = (iptc_handle_t *) malloc(sizeof(iptc_handle_t));
	if (!handle) {
		fprintf(stderr, "out of memory\n");
		exit(1);
	}
	memset(handle, 0, sizeof(iptc_handle_t));

	program_name = "iptables";
	program_version = NETFILTER_VERSION;

	ret = do_command(argc, argv, &table, handle);
	if (ret)
		ret = iptc_commit(handle);

	if (!ret)
		fprintf(stderr, "iptables: %s\n",
			iptc_strerror(errno));

	exit(!ret);
}
