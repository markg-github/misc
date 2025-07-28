

<#
  .SYNOPSIS
  Wrap browser_tabs script and sort by count and grep for arg.

  .DESCRIPTION

  .EXAMPLE

  .NOTES
  May 31, 2025: Initial revision
#>

param (
    # [string] $workspace,
    [string] $workspace_directory = "$env:LOCALAPPDATA\Microsoft\Edge\User Data",
    [string] $workspace_profile = "Default",
    [string] $workspace_cachefile = "Workspaces\WorkspacesCache",
    [string] $process = "msedge",
    [int] $max_count = 100,
    [switch] $sortbycount = $false
)



# one error at a time
# comment out to keep running after error
# valid values: Break, Continue (default), Ignore, Inquire, SilentlyContinue, Stop, Suspend
$ErrorActionPreference = 'Stop'

# valid values: Stop, Inquire, Continue, SilentlyContinue (default)
# $DebugPreference = 'Continue'

# for wrappers implemented as aliases and for wrapper functions
$module_directory = ".\"
. ($module_directory + "the-aliases.ps1")


function Get-Workspaces {
    
}

# #################################
# end "template"
# #################################

# a function/non-alias way to add wrappers

# Set-Alias -name "bt" -value Get-BrowserTabs
function BT1 {
    Get-BrowserTabs
}

# Set-Alias -name "btsort" -value Sort-Tabs
function Sort-BT {
    Sort-Tabs
}

# Set-Alias -name "btgrep" -value Grep-Tabs
function Grep-BT {
    param([string] $thePattern)
    Grep-Tabs $thePattern
}
# Set-Alias -name "btsg" -value Grep-Sort-Tabs
function Sort-Grep-BT {
    param([string] $thePattern)

    Grep-Sort-Tabs $thePattern
}

