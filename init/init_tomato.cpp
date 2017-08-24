/*
   Copyright (c) 2015, The CyanogenMod Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include <android-base/properties.h>

#include "property_service.h"
#include "vendor_init.h"
#include "util.h"
#include "init_msm8916.h"

using android::base::GetProperty;
using android::base::SetProperty;

static int display_density = 320;

static void import_cmdline(const std::string& key,
        const std::string& value, bool for_emulator __attribute__((unused)))
{
    if (key.empty()) return;

    if (key == "panel.xres" && value == "1080") {
        display_density = 480;
    }
}

void init_target_properties()
{
    std::string device;

    device = GetProperty("ro.lineage.device", "");
    if (device != "tomato")
        return;

    char density[5];
    import_kernel_cmdline(0, import_cmdline);
    snprintf(density, sizeof(density), "%d", display_density);
    property_set("ro.sf.lcd_density", density);
    if (display_density == 480) {
        SetProperty("ro.product.model", "YU5510");
        SetProperty("dalvik.vm.heapstartsize", "16m");
        SetProperty("dalvik.vm.heapgrowthlimit", "192m");
        SetProperty("dalvik.vm.heapsize", "512m");
        SetProperty("dalvik.vm.heaptargetutilization", "0.75");
        SetProperty("dalvik.vm.heapminfree", "2m");
        SetProperty("dalvik.vm.heapmaxfree", "8m");
    } else {
        SetProperty("ro.product.model", "AO5510");
        SetProperty("dalvik.vm.heapstartsize", "8m");
        SetProperty("dalvik.vm.heapgrowthlimit", "192m");
        SetProperty("dalvik.vm.heapsize", "512m");
        SetProperty("dalvik.vm.heaptargetutilization", "0.75");
        SetProperty("dalvik.vm.heapminfree", "512k");
        SetProperty("dalvik.vm.heapmaxfree", "8m");
    }
}
