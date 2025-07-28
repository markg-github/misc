
function Get-BrowserTabs {
    param (

        [switch] $sortbycount = $false
    )

    if ($sortbycount) {
        .\browser_tabs.ps1 -sortbycount
    }
    else {
        .\browser_tabs.ps1 
    }
    
}
function Sort-Tabs {
    Get-BrowserTabs -sortbycount
}

function Grep-Sort-Tabs {
    param (
        [string] $thePattern
    )
    $tempO = Get-BrowserTabs -sortbycount
    $tempO | out-string -stream | select-string $thePattern
}

function Grep-Tabs {
    param (
        [string] $thePattern
    )
    Get-BrowserTabs | out-string -stream | select-string $thePattern
}



Set-Alias -name "bt" -value Get-BrowserTabs
Set-Alias -name "btsort" -value Sort-Tabs

Set-Alias -name "btgrep" -value Grep-Tabs
Set-Alias -name "btsg" -value Grep-Sort-Tabs


# Set-Alias -name "bt-sortbycount" -value ".\browser_tabs.ps1 -sortbycount"
# # Set-Alias -name "bt-sortbycount" -value ".\browser_tabs.ps1" -option "sortbycount"

# Set-Alias -name "bt-sortbycountgrep" -value "bt-sortbycount | out-string -stream | select-string am"

