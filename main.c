/*
 *
 * Copyright 2023 Kenichi Yasukata
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <libelisa.h>
#include <libelisa_extra/map.h>
#include <libelisa_extra/irq.h>

#define BASE_GPA (1UL << 37) /* TODO: ensure no-overlap with others */

#define ENV_APPLIB_FILE_STR "ELISA_APPLIB_FILE"

int elisa__server_exit_cb(uint64_t *user_any __attribute__((unused)))
{
	return 0;
}

int elisa__server_cb(int sockfd __attribute__((unused)),
		     uint64_t *user_any,
		     struct elisa_map_req **map_req,
		     int *map_req_cnt,
		     uint64_t *entry_function)
{
	void *handle = NULL;
	{
		const char *filename;
		assert((filename = getenv(ENV_APPLIB_FILE_STR)) != NULL);
		{
			int map_req_num = 0;
			assert(!elisa_create_program_map_req(filename,
							     BASE_GPA,
							     &handle,
							     map_req,
							     map_req_cnt,
							     &map_req_num));
		}
	}
	assert(handle);
	assert(((void *)(*entry_function = (uint64_t) dlsym(handle, "entry_function"))) != NULL);
	*user_any = 0;
	return 0;
}

int elisa__client_cb(int sockfd __attribute__((unused)))
{
	return 0;
}

int elisa__client_work(void)
{
	long ret;
	printf("enter sub EPT context and get a return value\n");
	elisa_disable_irq_if_enabled();
	ret = elisa_gate_entry(0, 0, 0, 511 /* rcx */, 0, 0);
	vmcall_sti();
	printf("return value is %ld\n", ret);
	return 0;
}

int elisa__exec_init(void)
{
	return 0;
}
