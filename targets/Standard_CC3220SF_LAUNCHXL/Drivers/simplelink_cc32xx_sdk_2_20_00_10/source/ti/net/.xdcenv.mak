#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /vagrant/SDK_Q2_GA_Gen2_Only/sdk_root/kernel/tirtos/packages
override XDCROOT = /opt/ti/xdctools_3_50_07_20_core
override XDCBUILDCFG = /vagrant/SDK_Q2_GA_Gen2_Only/sdk_root/source/ti/net/ns.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = TIPOSIX_REPO="/vagrant/SDK_Q2_GA_Gen2_Only/sdk_root/source" ti.targets.arm.elf.M4="/opt/ti/ccs-latest/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS" gnu.targets.arm.M4="/opt/ti/ccs-latest/ccsv8/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major" iar.targets.arm.M4="/opt/iar/arm/latest"
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /vagrant/SDK_Q2_GA_Gen2_Only/sdk_root/kernel/tirtos/packages;/opt/ti/xdctools_3_50_07_20_core/packages;../..
HOSTOS = Linux
endif
