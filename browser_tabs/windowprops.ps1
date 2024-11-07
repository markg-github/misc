Add-Type @"
using System;
using System.Runtime.InteropServices;

public class User32 {
    [DllImport("user32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool EnumWindows(EnumWindowsProc lpEnumFunc, IntPtr lParam);

    public delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);

    [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
    public static extern int GetWindowText(IntPtr hWnd, System.Text.StringBuilder lpString, int nMaxCount);

    [DllImport("user32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool IsWindowVisible(IntPtr hWnd);
}
"@

# Define a script block to get window properties
$windowInfo = {
    $windows = @()
    $null = [User32]::EnumWindows({ param ($hWnd, $lParam)
        $title = New-Object System.Text.StringBuilder 256
        [User32]::GetWindowText($hWnd, $title, $title.Capacity) | Out-Null

        if ($title.ToString() -ne "" -and [User32]::IsWindowVisible($hWnd)) {
            $windows += [PSCustomObject]@{
                Handle = $hWnd
                Title = $title.ToString()
            }
        }
        return $true
    }, [IntPtr]::Zero)
    return $windows
}

# Get window properties
$windowProperties = & $windowInfo

# Display the window properties
$windowProperties | Format-Table -AutoSize
