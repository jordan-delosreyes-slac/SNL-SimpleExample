# Load RUCKUS environment and library
source -quiet $::env(RUCKUS_DIR)/vivado_proc.tcl

# Check for version 2021.1 of Vivado (or later)
if { [VersionCheck 2021.1] < 0 } {exit -1}

# Load base sub-modules
loadRuckusTcl $::env(PROJ_DIR)/../../submodules/surf
loadRuckusTcl $::env(PROJ_DIR)/../../submodules/axi-pcie-core/hardware/XilinxKcu1500

# Load shared source code
loadRuckusTcl $::env(PROJ_DIR)/../../shared

# Load local source Code
loadSource      -dir "$::DIR_PATH/hdl"
loadConstraints -dir "$::DIR_PATH/hdl"

# Load the simulation testbed
loadSource -sim_only -dir "$::DIR_PATH/tb"
set_property top {Kcu1500Tb} [get_filesets sim_1]

# Updating impl_1 strategy
set_property strategy Performance_ExplorePostRoutePhysOpt [get_runs impl_1]
