param(
    [string]$Action = "vs2022" # default action if none is provided
)





# ---------------------------------------
# Build Premake (static lib)
# ---------------------------------------

# Get absolute path to premake submodule
$PremakeDir = Resolve-Path "vendor\premake"
$PremakeExe = Join-Path $PremakeDir "bin\release\premake5.exe"

Write-Host "==> Checking Premake build..." -ForegroundColor Cyan

# Build Premake if not already built
if (-Not (Test-Path $PremakeExe)) {
    Write-Host "==> premake5.exe not found, building Premake..." -ForegroundColor Yellow
    Push-Location $PremakeDir
    .\bootstrap.bat
    Pop-Location
}

# Verify build succeeded
if (-Not (Test-Path $PremakeExe)) {
    Write-Error "Premake build failed. Please check the bootstrap output."
    exit 1
}





# ---------------------------------------
# Build Assimp (static lib)
# ---------------------------------------

$AssimpDir = ".\vendor\assimpPremake"
$AssimpBuild = "$AssimpDir\build"
$AssimpDebugLib   = "$AssimpBuild\lib\Debug\assimpPremake.lib"
$AssimpReleaseLib = "$AssimpBuild\lib\Release\assimpPremake.lib"

if (!(Test-Path $AssimpDebugLib) -or !(Test-Path $AssimpReleaseLib)) {
    Write-Host "Configuring and building Assimp..."

    if (!(Test-Path $AssimpBuild)) {
        New-Item -ItemType Directory -Force -Path $AssimpBuild | Out-Null
    }

    cmake -S $AssimpDir -B $AssimpBuild -G "Visual Studio 17 2022"

    cmake --build $AssimpBuild --config Debug
    $debugLib = Get-ChildItem "$AssimpBuild\lib\Debug" -Filter *.lib | Select-Object -First 1
    if ($debugLib) {
        Rename-Item -Path $debugLib.FullName -NewName "assimpPremake.lib" -Force
    }

    cmake --build $AssimpBuild --config Release
    $releaseLib = Get-ChildItem "$AssimpBuild\lib\Release" -Filter *.lib | Select-Object -First 1
    if ($releaseLib) {
        Rename-Item -Path $releaseLib.FullName -NewName "assimpPremake.lib" -Force
    }

}
else {
    Write-Host "Assimp already built. Skipping..."
}





# ---------------------------------------
# Gen Proj files (static lib)
# ---------------------------------------

Write-Host "==> Using $PremakeExe" -ForegroundColor Green

# Run Premake with the chosen action (vs2022, vs2017, gmake2, etc.)
& $PremakeExe $Action

if ($LASTEXITCODE -eq 0) {
    Write-Host "==> Project files generated successfully for $Action!" -ForegroundColor Green
} else {
    Write-Error "Premake failed with exit code $LASTEXITCODE"
    exit $LASTEXITCODE
}
