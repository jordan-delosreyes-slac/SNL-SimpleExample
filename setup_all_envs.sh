# Setup Vivado/Vitis
source /sdf/group/faders/tools/xilinx/2025.1/Vivado/2025.1/settings64.sh

# Setup VCS
source /sdf/group/faders/tools/synopsys/vcs/X-2025.06/settings.sh

# SNL Python Environments
source firmware/submodules/snl/scripts/setup_env.sh
source firmware/submodules/snl-py/scripts/setup_env.sh

# Setup Rogue Using Conda
conda activate rogue_tag
