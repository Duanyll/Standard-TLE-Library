g++ example.cpp -o example.exe --std=gnu++17
g++ example_std.cpp -o example_std.exe --std=gnu++17
g++ example_dm.cpp -o example_dm.exe --std=gnu++17
while($true) {
    ./example_dm.exe > example.in
    "Data maked."
    Get-Content example.in | ./example_std.exe > example_std.out
    "Std called."
    Get-Content example.in | ./example_std.exe > example.out
    "Program called."
    if ($LASTEXITCODE) {
        "RE!"
        break
    }
    $result = Compare-Object (Get-Content example.out) (Get-Content example_std.out)
    if ($result) {
        Write-Host $result
        break
    }
}
