/*
 * Copyright (C) 2014 Cloudius Systems, Ltd.
 *
 * This work is open source software, licensed under the terms of the
 * BSD license as described in the LICENSE file in the top-level directory.
 */

#include "hardware.hh"
#include "json/formatter.hh"
#include "autogen/hardware.json.hh"
#include "processor.hh"
#include <osv/sched.hh>
#include <boost/algorithm/string.hpp>

namespace httpserver {

namespace api {

namespace hardware {

using namespace std;
using namespace json;
using namespace hardware_json;

void init(routes& routes)
{
    hardware_json_init_path();

    processorFeatures.set_handler([](const_req req)
    {
        std::vector<std::string> flags;
        boost::split(flags, processor::features_str(), boost::is_any_of("\t "));
        CPU_flags res;
        for(string flag: flags) {
            if (flag == "sse3") {
                res.sse3 = true;
            }
            else if (flag == "ssse3") {
                res.ssse3 = true;
            }
            else if (flag == "cmpxchg16b") {
                res.cmpxchg16b = true;
            }
            else if (flag == "sse4_1") {
                res.sse4_1 = true;
            }
            else if (flag == "sse4_2") {
                res.sse4_2 = true;
            }
            else if (flag == "x2apic") {
                res.x2apic = true;
            }
            else if (flag == "tsc_deadline") {
                res.tsc_deadline = true;
            }
            else if (flag == "xsave") {
                res.xsave = true;
            }
            else if (flag == "avx") {
                res.avx = true;
            }
            else if (flag == "rdrand") {
                res.rdrand = true;
            }
            else if (flag == "clflush") {
                res.clflush = true;
            }
            else if (flag == "fsgsbase") {
                res.fsgsbase = true;
            }
            else if (flag == "repmovsb") {
                res.repmovsb = true;
            }
            else if (flag == "gbpage") {
                res.gbpage = true;
            }
            else if (flag == "invariant_tsc") {
                res.invariant_tsc = true;
            }
            else if (flag == "kvm_clocksource") {
                res.kvm_clocksource = true;
            }
            else if (flag == "kvm_clocksource2") {
                res.kvm_clocksource2 = true;
            }
            else if (flag == "kvm_clocksource_stable") {
                res.kvm_clocksource_stable = true;
            }
            else if (flag == "kvm_pv_eoi") {
                res.kvm_pv_eoi = true;
            }
            else if (flag == "xen_clocksource") {
                res.xen_clocksource = true;
            }
            else if (flag == "xen_vector_callback") {
                res.xen_vector_callback = true;
            }
            else if (flag == "xen_pci") {
                res.xen_pci = true;
            }
        }
        return res;
    });

    processorCount.set_handler([](const_req req)
    {
        return sched::cpus.size();
    });
}

}
}
}
