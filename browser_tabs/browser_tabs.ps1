


<#
  .SYNOPSIS
  Show open and closed Edge (browser) Workspaces.

  .DESCRIPTION

  .EXAMPLE

  .NOTES
  Modified Date:  Nov 5, 2024
#>

param (
    [string] $workspace,
    [string] $workspace_directory = "$env:LOCALAPPDATA\Microsoft\Edge\User Data",
    [string] $workspace_profile = "Default",
    [string] $workspace_cachefile = "Workspaces\WorkspacesCache",
    [string] $process = "msedge",
    [int] $max_count = 100
)

# one error at a time
# comment out to keep running after error
# valid values: Break, Continue (default), Ignore, Inquire, SilentlyContinue, Stop, Suspend
$ErrorActionPreference = 'Stop'

# valid values: Stop, Inquire, Continue, SilentlyContinue (default)
# $DebugPreference = 'Continue'

$PSScriptRoot = "c:\data\dev\git\markg\browser_tabs\"
. ($PSScriptRoot + "windowprops2.ps1")


# #################################
# end "template"
# #################################

# Ensure you have Edge and PowerShell installed on your system



# Define a function to get workspace names from a profile
function Get-Workspaces {
    
    $PreferencesPath = Join-Path -Path $workspace_directory -ChildPath $workspace_profile
    $PreferencesPath = Join-Path -Path $PreferencesPath -ChildPath $workspace_cachefile
    
    if (Test-Path -Path $PreferencesPath) {
        $Preferences = Get-Content -Path $PreferencesPath -Raw | ConvertFrom-Json
        
        if ($Preferences.workspaces) {
            # return $Preferences.workspaces | ForEach-Object { $_.name }
            return $Preferences.workspaces
        }
    }
    
    return @()
}

function Get-WindowTitles {
    param($process)
    $edges = Get-Process -Name $process
    $titles = @()
    foreach ($edge in $edges) {
        $titles += $edge.MainWindowTitle
    }
    return $titles
}

function Get-Processes {
    param($process)
    $edges = Get-Process -Name $process
    return $edges
}



# Initialize an array to store workspace names
$Workspaces = @()
$workspace_names = @()

$workspaces = Get-Workspaces 
foreach ($ws in $workspaces) {
    $workspace_names += $ws.name
}

function Find-Workspace {
    param($name_, $windows_)
    foreach ($window in $windows_) {
        if ($name_ -eq $window.Title) {
            return $true
                
        }

    }
    return $false
}

$windows = @()
$windows = Get-Windows
# Get-Processes $process
$output_array = @()

foreach ($ws in $workspaces) {
    $is_open = Find-Workspace $ws.name $windows
    $temp = new-object -typename psobject
    if ($is_open) {
        $temp | add-member -membertype noteproperty -name "open workspaces" -value $ws.name
        $temp | add-member -membertype noteproperty -name "closed workspaces" -value ""
    
    }
    else {
        $temp | add-member -membertype noteproperty -name "open workspaces" -value ""
        $temp | add-member -membertype noteproperty -name "closed workspaces" -value $ws.name
    
    }
    $temp | add-member -membertype noteproperty -name "tab count" -value $ws.count.ToString()

    $output_array += $temp

}

# exit 1


# Print the names of all workspaces

function unused3 {
    foreach ($ws in $workspace_names) {
        $temp = new-object -typename psobject
        $is_open = Find-Workspace $ws $EdgeWindowTitles
        if ($is_open) {
            $temp | add-member -membertype noteproperty -name "open workspaces" -value $ws
            $temp | add-member -membertype noteproperty -name "closed workspaces" -value ""
    
        }
        else {
            $temp | add-member -membertype noteproperty -name "open workspaces" -value ""
            $temp | add-member -membertype noteproperty -name "closed workspaces" -value $ws
    
        }
        $temp | add-member -membertype noteproperty -name "tab count" -value $ws.count.ToString()

        $output_array += $temp

    }
}

function unused {

    $Workspaces | ForEach-Object { 
    
        $temp = new-object -typename psobject
        if ($_.accent -and $_.workspaceFluidStatus -eq 0) {
            $temp | add-member -membertype noteproperty -name "open workspaces" -value "?"
            $temp | add-member -membertype noteproperty -name "closed workspaces" -value "?"

        }
        elseif ($_.accent -and $_.workspaceFluidStatus -eq 2) {
            $temp | add-member -membertype noteproperty -name "open workspaces" -value $_.name
            $temp | add-member -membertype noteproperty -name "closed workspaces" -value ""

        }
        elseif (-not $_.accent -and $_.workspaceFluidStatus -eq 0) {
            $temp | add-member -membertype noteproperty -name "closed workspaces" -value $_.name
            $temp | add-member -membertype noteproperty -name "open workspaces" -value ""

        }
        elseif (-not $_.accent -and $_.workspaceFluidStatus -eq 2) {
            $temp | add-member -membertype noteproperty -name "open workspaces" -value "?"
            $temp | add-member -membertype noteproperty -name "closed workspaces" -value "?"

        }
        else {
            $temp | add-member -membertype noteproperty -name "open workspaces" -value $_.workspaceFluidStatus.ToString()
            $temp | add-member -membertype noteproperty -name "closed workspaces" -value $_.workspaceFluidStatus.ToString()

        }
        $temp | add-member -membertype noteproperty -name "tab count" -value $_.count.ToString()

        $output_array += $temp
    }
}

function unused2 {
    # Print the names of all workspaces that correspond to Edge browser windows
    foreach ($WindowTitle in $EdgeWindowTitles) {
        if ($WorkspaceNames -contains $WindowTitle) {
            Write-Output $WindowTitle
        }
    }
}

$output_array | format-table
