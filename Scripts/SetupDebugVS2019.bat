@echo off
echo ==========================================
echo Setup GojoEngine and Projects [DEBUG] VS2019
echo ==========================================

REM Go up one directory
cd ..

REM Create build directory if it doesn't exist
if not exist Build mkdir Build

REM Change to build directory
cd Build

REM Run cmake with VS2019 generator (x64 default)
echo ==========================================
echo Generation of GojoEngine and Projects [VS2019]
echo ==========================================
cmake .. -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Debug

REM Build the project
echo ==========================================
echo Building of GojoEngine and Projects [Debug]
echo ==========================================
cmake --build . --config Debug

echo ==========================================
echo Installation [Debug]
echo ==========================================
cmake --install . --config Debug

pause