@echo off
echo ==========================================
echo Setup GojoEngine and Projects [DEBUG]
echo ==========================================

REM Go up one directory
cd ..

REM Create build directory if it doesn't exist
if not exist Build mkdir Build

REM Change to build directory
cd Build

REM Run cmake from build directory pointing to parent
echo ==========================================
echo Generation of GojoEngine and Projects
echo ==========================================
cmake .. -DCMAKE_BUILD_TYPE=Debug

REM Build the project
echo ==========================================
echo Building of GojoEngine and Projects
echo ==========================================
cmake --build . --config Debug

echo ==========================================
echo Installation
echo ==========================================
cmake --install . --config Debug

pause