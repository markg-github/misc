





param (
    [string] $workspace,
    [string] $workspace_directory = "$env:LOCALAPPDATA\Microsoft\Edge\User Data",
    [string] $workspace_profile = "Default",
    [string] $workspace_cachefile = "Workspaces\WorkspacesCache",
    # [Parameter(Mandatory = $True, HelpMessage = "process")]
    [string] $process = "msedge",
    [int] $max_count = 100,
    # [Parameter(HelpMessage = "Sort by tab count")]
    [switch] $sortbycount = $false
)

write-host "test"



