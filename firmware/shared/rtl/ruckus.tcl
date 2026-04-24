# Load RUCKUS environment and library
source -quiet $::env(RUCKUS_DIR)/vivado_proc.tcl

# Load RTL source Code
loadSource -dir "$::DIR_PATH/rtl"

# Load HLS .ZIP output file
if { [get_ips Lenet5_NN] eq ""  } {
   loadZipIpCore  -repo_path $::env(IP_REPO) -path "$::DIR_PATH/ip/processNetwork.zip"
   create_ip -name Lenet5_NN -vendor SLAC -library hls -version 1.0 -module_name processNetwork_0
}
