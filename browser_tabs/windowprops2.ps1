Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;

public class myUser32 {
    [DllImport("user32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool EnumWindows(EnumWindowsProc lpEnumFunc, IntPtr lParam);

    public delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);

    [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
    public static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

    [DllImport("user32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool IsWindowVisible(IntPtr hWnd);

    [DllImport("user32.dll", SetLastError = true)]
    public static extern int GetWindowThreadProcessId(IntPtr hWnd, out int lpdwProcessId);
}
"@

function Get-Windows {
    # Define a script block to get window properties
    $script:windows = @()
    $windowInfo = {
        $callback = [myUser32+EnumWindowsProc] {
            param ($hWnd, $lParam)
        
            $title = New-Object System.Text.StringBuilder 256
            [myUser32]::GetWindowText($hWnd, $title, $title.Capacity) | Out-Null
            # Write-Host "Window Found: Handle = $hWnd, Title = $($title.ToString())"

            if ($title.ToString() -ne "" -and [myUser32]::IsWindowVisible($hWnd)) {
                $mypid = 0
                [myUser32]::GetWindowThreadProcessId($hWnd, [ref]$mypid)
                $script:windows += [PSCustomObject]@{
                    Handle = $hWnd
                    Title  = $title.ToString()
                    PID = $mypid
                }
                # Write-Output "Window Found: Handle = $hWnd, Title = $($title.ToString())"
            }
            return $true
        }
        $null = [myUser32]::EnumWindows($callback, [IntPtr]::Zero)
        return $script:windows
    }

    # Get window properties
    $windowProperties = & $windowInfo

    # Display the window properties
    # $windowProperties | Format-Table -AutoSize

    return $windowProperties
}
