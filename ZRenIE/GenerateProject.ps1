param(
    [string]$Action = "vs2022" # default action if none is provided
)

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

Write-Host "==> Using $PremakeExe" -ForegroundColor Green

# Run Premake with the chosen action (vs2022, vs2017, gmake2, etc.)
& $PremakeExe $Action

if ($LASTEXITCODE -eq 0) {
    Write-Host "==> Project files generated successfully for $Action!" -ForegroundColor Green
} else {
    Write-Error "Premake failed with exit code $LASTEXITCODE"
    exit $LASTEXITCODE
}
