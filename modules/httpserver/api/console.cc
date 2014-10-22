/*
 * console.cc
 *
 *  Created on: Oct 21, 2014
 *      Author: amnon
 */


#include "env.hh"
#include "autogen/console.json.hh"
#include <stdlib.h>
#include <drivers/memory-console.hh>
#include <drivers/console.hh>
#include "handlers.hh"

namespace httpserver {

namespace api {

namespace console {

using namespace json;
using namespace std;
using namespace console_json;

static ::console::memory_console mem_console;

void init(routes& routes)
{
    console_json_init_path("Console management API");
    ::console::console_driver_add(&mem_console);
    function_handler* h = new function_handler ([](const_req req, http::server::reply& rep) {
    	return mem_console.get_output();
    }, "txt");
    console_output.set_handler(h);

    console_input.set_handler([](const_req req) {
    	mem_console.add_input(req.get_query_param("text"));
    	return "";
    });

}

}
}
}



